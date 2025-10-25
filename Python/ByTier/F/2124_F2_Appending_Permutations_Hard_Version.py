# Problem: CF 2124 F2 - Appending Permutations (Hard Version)
# https://codeforces.com/contest/2124/problem/F2

"""
F2. Appending Permutations (Hard Version)

Purpose:
This code solves a dynamic programming problem where we need to count the number of valid permutations of length n that can be constructed using a special operation and satisfies given restrictions.

The operation allows appending a cyclic shift of [1, 2, ..., s] to the array. The solution uses dynamic programming with interval compression and difference arrays for optimization.

Algorithms/Techniques:
- Dynamic Programming with prefix sums and difference arrays
- Interval compression using min2 function (min function)
- Modular arithmetic with MOD = 998244353

Time Complexity: O(n^3) where n <= 5000, due to nested loops over n
Space Complexity: O(n^2) for the 2D arrays b and hav, and O(n) for dp array

Input Format:
- t test cases
- For each test case:
  - n, m (array length and number of restrictions)
  - m lines of i, x indicating a[i] != x

Output:
- Number of valid arrays modulo 998244353
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
MOD = 998244353


def min2(x, y):
    return x if x < y else y


def solve():
    n, m = map(int, input().split())
    # b[i][j] stores the minimum index such that prefix i does not allow placing value j
    b = [[n] * (n + 1) for _ in range(n + 1)]
    for _ in range(m):
        # Convert to 0-based indexing
        i, x = (num - 1 for num in map(int, input().split()))
        # Mark restriction that at position i, we cannot use value x
        b[i][x] = i
    # Propagate minimum values backwards to get valid range constraints
    for p in range(n - 1, -1, -1):
        for i in range(n):
            b[p][i] = min2(b[p][i], b[p + 1][i + 1])
    
    # hav[i][j] is a difference array for helping in interval updates
    hav = [[0] * (n + 1) for _ in range(n + 2)]
    # dp[l] represents number of ways to build prefix of length l
    dp = [1] + [0] * n
    for l in range(n + 1):
        l1 = l + 1
        # Process current prefix l to compute how many valid extensions exist
        for i in range(1, n - l + 1):
            x = dp[l]
            # Subtract invalid cases using previous dp values
            if l - i >= 0 and b[l - i][0] >= l:
                x -= dp[l - i]
            # Compute right boundary of valid range from constraint array
            r1 = b[l][i] + 1
            # Apply difference array logic - add to segment [l1, r1)
            hav[l1][i] = (hav[l1][i] + x) % MOD
            hav[r1][i] = (hav[r1][i] - x) % MOD
        # Propagate prefix sums in the difference array
        for i in range(n + 1):
            hav[l1][i] = (hav[l1][i] + hav[l][i]) % MOD
        # Update dp with new computed values using accumulated sum from hav
        for i in range(1, b[l][0] - l + 1):
            dp[l + i] = (dp[l + i] + dp[l] + hav[l][i]) % MOD
    return dp[-1]


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/