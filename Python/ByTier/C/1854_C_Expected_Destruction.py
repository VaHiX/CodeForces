# Problem: CF 1854 C - Expected Destruction
# https://codeforces.com/contest/1854/problem/C

"""
Expected Destruction - Solution

This problem involves calculating the expected number of seconds until a set S of integers becomes empty,
with specific rules for adding and removing elements. The approach uses dynamic programming and
mathematical expectations to compute the result.

Key steps:
1. Preprocess the set S into 0-indexed form.
2. Compute initial result based on total sum and element positions.
3. Use dynamic programming to calculate transition probabilities.
4. Adjust final answer using modular arithmetic and inverse modulo.

Time Complexity: O(m^2)
Space Complexity: O(m^2)

Algorithms/Techniques:
- Dynamic Programming (DP)
- Modular Arithmetic
- Inverse Modulo (Fermat's Little Theorem)
"""

n, m = map(int, input().split())
a = list(map(lambda x: int(x) - 1, input().split()))

# Calculate initial value of answer based on total possible steps minus sum of positions
ans = m * n - sum(a)

mod = 10**9 + 7
# Precompute modular inverse of 2 (needed for probability calculations)
inv2 = pow(2, mod - 2, mod)

# Initialize DP table: dp[i][j] represents transition probability or count
dp = [[0] * (m + 1) for i in range(m + 1)]

# Set base transitions
for i in range(n - 1):
    dp[a[i + 1]][a[i]] = 1

# Propagate transitions using dynamic programming
for j in range(m):
    for k in range(j):
        dp[j][k] %= mod
        # Update probabilities going right and down
        dp[j][k + 1] += dp[j][k] * inv2 % mod
        dp[j + 1][k] += dp[j][k] * inv2 % mod

# Final adjustment using DP values and modulo
for i in range(m):
    ans -= dp[i][i] * (m - i)
    ans %= mod

print(ans)


# https://github.com/VaHiX/CodeForces/