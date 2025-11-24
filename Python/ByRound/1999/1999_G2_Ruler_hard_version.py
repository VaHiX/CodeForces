# Problem: CF 1999 G2 - Ruler (hard version)
# https://codeforces.com/contest/1999/problem/G2

"""
Algorithm: ternary search with adjustments
Approach:
- Use a ternary search strategy to find the missing number x in range [2, 999].
- For each query, we use two values a and b derived from the current search range.
- Based on the response from the ruler, we adjust our search boundaries.
- The key insight is that:
    - If the measured area equals (a+1)*(b+1), then x is in the left third.
    - If the measured area equals a*b, then x is in the right third.
    - Otherwise, x is in the middle third.
- Handle the final three elements carefully with a special case after the main loop.

Time Complexity: O(log_3(998)) = O(1) since the number of queries is bounded by 7.
Space Complexity: O(1) - only using a few variables for tracking.
"""

def solve():
    l, r = 1, 999  # Initialize search bounds
    while r - l > 2:  # Continue until we have at most 3 candidates left
        # Compute a and b as the two thirds of the current range
        a = (2 * l + r) // 3  # First third point
        b = (2 * r + l) // 3  # Second third point

        # Query the rectangle of size a x b
        print(f"? {a} {b}")
        resp = int(input())

        # Analyze the response to adjust the search range
        if resp == (a + 1) * (b + 1):  # If the result is as if x was in the left third
            r = a  # Adjust upper bound
        elif resp == a * b:  # If the result matches the left side (indicating x is not in range)
            l = b  # Adjust lower bound
        else:  # Otherwise, x is in the middle third
            l, r = a, b  # Narrow search to middle

    # Handle the final 3 candidates
    if r - l == 2:
        # Query a special case to determine the exact value of x
        print(f"? 1 {l + 1}")
        resp = int(input())

        if resp == l + 1:  # If it's measured as correct, x is l+1
            l = l + 1
        else:  # Otherwise x is l+1 (corrected by the query result)
            r = l + 1

    print(f"! {r}")  # Output the determined value


def main():
    tt = int(input())
    for _ in range(tt):
        solve()


main()


# https://github.com/VaHiX/CodeForces/