# Problem: CF 2131 B - Alternating Series
# https://codeforces.com/contest/2131/problem/B

"""
B. Alternating Series
time limit per test2 seconds
memory limit per test256 megabytes

This program generates a "good" array of length n based on specific rules:
- Adjacent elements have negative product (alternating signs).
- All subarrays of length >= 2 have positive sum.
- The output is lexicographically smallest among all good arrays of same length.

Approach:
1. For odd n:
   - Generate (n//2) pairs of (-1, 3) followed by a final -1 to ensure the sum is 1.
2. For even n:
   - Generate (n//2 - 1) pairs of (-1, 3) followed by (-1, 2) to satisfy conditions.
   
Time Complexity: O(n) per test case - linear in the length of the array
Space Complexity: O(1) - output is generated on the fly, no extra space used

Algorithms/Techniques:
- Greedy construction with alternating values
- Mathematical handling of parity (odd/even cases)
"""

def generate_alternating_series(n):
    """Generate the alternating series based on the given length n."""
    if n % 2 == 1:  # If n is odd
        # Generate (n//2) pairs of (-1, 3), then add a final -1
        return "-1 3 " * (n // 2) + "-1"
    else:  # If n is even
        # Generate (n//2 - 1) pairs of (-1, 3), then end with (-1, 2)
        return "-1 3 " * (n // 2 - 1) + "-1 2"


def main():
    num_test_cases = int(input())
    for _ in range(num_test_cases):
        sequence_length = int(input())
        print(generate_alternating_series(sequence_length))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/