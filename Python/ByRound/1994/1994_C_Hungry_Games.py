# Problem: CF 1994 C - Hungry Games
# https://codeforces.com/contest/1994/problem/C

"""
Algorithm: Prefix Sum with Reverse Iteration
Techniques: Two Pointers / Prefix Sum

Time Complexity: O(n) per test case, where n is the number of mushrooms.
Space Complexity: O(1) excluding the input storage.

This solution uses a reverse iteration approach to efficiently count valid subsegments.
We iterate from the end of the array and maintain a running sum (total).
If the current sum is within the toxicity limit x, we count how many valid subsegments
can be formed ending at the current index. Otherwise, we reset the sum to zero.
"""

def main():
    t = int(input().strip())
    results = []
    for _ in range(t):
        n, x = map(int, input().strip().split())
        a = list(map(int, input().strip().split()))
        sec = 0
        total = 0
        # Iterate from right to left
        for i in range(n - 1, -1, -1):
            total += a[i]
            # If the accumulated toxicity is within limit
            if total <= x:
                # Add the number of valid subsegments ending at position i
                sec += i + 1
            else:
                # Reset the sum if it exceeds the limit
                total = 0
        results.append(str(sec))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/