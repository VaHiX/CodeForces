# Problem: CF 2124 F1 - Appending Permutations (Easy Version)
# https://codeforces.com/contest/2124/problem/F1

"""
Problem: F1. Appending Permutations (Easy Version)

Algorithm/Techniques:
- Dynamic Programming with Difference Array Techniques
- Modular Arithmetic for large results
- Preprocessing restrictions and using min2 operations to track valid ranges

Time Complexity: O(n^3 + m)
Space Complexity: O(n^2)

This problem involves counting valid permutations of length n that can be formed by appending
cyclic shifts of arrays [1,2,...,s] and satisfying given position-value restrictions.

The approach uses dynamic programming with the concept of difference arrays:
- Preprocess the restrictions to build a table b representing valid ranges.
- Use a DP table (dp) to count permutations ending at each length.
- Use a helper array (hav) for range updates with difference array technique.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
MOD = 998244353


def min2(x, y):
    return x if x < y else y


def solve():
    n, m = map(int, input().split())
    # b[i][j] stores the minimum valid index for position i when considering permutations of length j
    b = [[n] * (n + 1) for _ in range(n + 1)]
    for _ in range(m):
        # Convert to 0-indexed for easier array access
        i, x = (num - 1 for num in map(int, input().split()))
        b[i][x] = i  # mark that at position i, we can't have value x
    # Propagate valid values forward using min2
    for p in range(n - 1, -1, -1):
        for i in range(n):
            b[p][i] = min2(b[p][i], b[p + 1][i + 1])
    
    # hav is used for difference array techniques to efficiently update ranges
    hav = [[0] * (n + 1) for _ in range(n + 2)]
    # dp[l] represents number of ways to form prefix of length l
    dp = [1] + [0] * n
    
    # Iterate over all possible prefixes of the final array
    for l in range(n + 1):
        l1 = l + 1
        # Process all positions i for current prefix length l
        for i in range(1, n - l + 1):
            x = dp[l]
            # If valid previous state and constraints are met
            if l - i >= 0 and b[l - i][0] >= l:
                x -= dp[l - i]
            # Determine right boundary of update
            r1 = b[l][i] + 1
            # Apply difference array update
            hav[l1][i] = (hav[l1][i] + x) % MOD
            hav[r1][i] = (hav[r1][i] - x) % MOD
        # Propagate differences downwards through the rows
        for i in range(n + 1):
            hav[l1][i] = (hav[l1][i] + hav[l][i]) % MOD
        # Use updated values to compute next dp states
        for i in range(1, b[l][0] - l + 1):
            dp[l + i] = (dp[l + i] + dp[l] + hav[l][i]) % MOD
    return dp[-1]


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/