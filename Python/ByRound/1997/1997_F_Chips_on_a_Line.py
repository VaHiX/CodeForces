# Problem: CF 1997 F - Chips on a Line
# https://codeforces.com/contest/1997/problem/F

"""
Algorithm: Dynamic Programming with Fibonacci-like Structure
Purpose: Count the number of ways to place n chips on x points such that the minimum number of chips after operations is exactly m.
Time Complexity: O(n * x * MAX_FIB * x) where MAX_FIB is the largest Fibonacci number used
Space Complexity: O(n * MAX_FIB) for DP table and auxiliary arrays

This solution uses a dynamic programming approach where we compute for each number of chips (from 0 to n) 
and each possible total position sum (represented as index), how many ways we can reach that state.
It also utilizes Fibonacci numbers to determine valid transformations.
"""

MOD = 998244353
N = 1005
M = 60005

# Precompute Fibonacci numbers (used to represent costs)
fib = [
    0,
    1,
    1,
    2,
    3,
    5,
    8,
    13,
    21,
    34,
    55,
    89,
    144,
    233,
    377,
    610,
    987,
    1597,
    2584,
    4181,
    6765,
    10946,
    17711,
    28657,
    46368,
    75025,
]
ans = [0] * (2 * M)
for i in range(1, M):
    ans[i] = i

# Compute minimum cost for each position using Fibonacci operations
for j in range(3, 25):
    for i in range(M):
        if i + fib[j] < 2 * M:
            ans[i + fib[j]] = min(ans[i + fib[j]], ans[i] + 1)

# dp[i][j] = number of ways to place i chips with total position sum j
dp = [[0] * M for _ in range(N)]
dp[0][0] = 1

n, x, m = map(int, input().split())

# For each point from 1 to x, update DP
for i in range(1, x + 1):
    # Loop through number of chips placed so far
    for j in range(n):
        # Loop through all possible total positions
        for k in range((j + 1) * fib[i]):
            if dp[j][k] > 0:
                # Place one chip at position i, add its Fibonacci value to cost
                dp[j + 1][k + fib[i]] = (dp[j + 1][k + fib[i]] + dp[j][k]) % MOD

finalans = 0
# Sum up all valid configurations where cost equals m
for i in range(1, M):
    if ans[i] == m:
        finalans = (finalans + dp[n][i]) % MOD

print(finalans)


# https://github.com/VaHiX/CodeForces/