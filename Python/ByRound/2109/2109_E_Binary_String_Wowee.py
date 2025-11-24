# Problem: CF 2109 E - Binary String Wowee
# https://codeforces.com/contest/2109/problem/E

"""
E. Binary String Wowee

Purpose:
This code solves a dynamic programming problem where we are given a binary string and need to count the number of ways
to perform exactly k operations, each selecting an index i such that s[i] = '0', and flipping all characters from the start up to index i.

Algorithms/Techniques:
- Dynamic Programming with state compression.
- Precomputed combination table for modular arithmetic.
- Bottom-up DP over string indices in reverse order.

Time Complexity: O(n * k^2)
Space Complexity: O(n * k)

The DP state tracks how many ways we can achieve a certain number of operations (j) at each step,
based on the current character in the string ('0' or '1') and transitions from previous states.
Combinations are computed using Pascal's triangle modulo 998244353 for combinatorial counts.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 998244353
mx = 501
comb = [[0] * mx for _ in range(mx)]
for i in range(mx):
    comb[i][0] = 1
    for j in range(1, i + 1):
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod


def solve():
    n, k = map(int, input().split())
    s = input()
    dp = [0] * (k + 1)
    dp[0] = 1  # Base case: one way to do 0 operations
    for i in range(n - 1, -1, -1):  # Traverse from right to left
        ndp = [0] * (k + 1)
        if s[i] == "0":  # If current character is '0', we can select it
            for j in range(k + 1):
                m = (j + 1) // 2  # Midpoint for choosing combinations
                res = 0
                for p in range(j // 2, j + 1):  # Iterate over valid previous states
                    res += dp[p] * comb[m][j - p]  # Add combinations * previous ways
                    res %= mod
                ndp[j] = res  # Store updated result
        else:  # If current character is '1', we cannot select it
            for j in range(k + 1):
                m = j // 2
                res = 0
                for p in range((j + 1) // 2, j + 1):  # Different iteration bounds for '1'
                    res += dp[p] * comb[m][j - p]
                    res %= mod
                ndp[j] = res
        dp = ndp  # Move to next state
    return dp[k]


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/