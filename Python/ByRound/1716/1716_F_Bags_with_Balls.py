# Problem: CF 1716 F - Bags with Balls
# https://codeforces.com/contest/1716/problem/F

"""
Algorithm: Bell Numbers and Stirling Numbers of the Second Kind
Purpose: Compute sum of F^k over all possible ways to take one ball from each of n bags,
         where each bag contains m balls numbered from 1 to m. F is the number of odd-numbered balls selected.
Time Complexity: O(k^2 + T*k), where T is number of test cases.
Space Complexity: O(k^2) for precomputing Stirling numbers.

The approach uses:
- Stirling numbers of the second kind (s[n][k]) to express power sums
- Fast exponentiation for modular arithmetic
- Linear recurrence to compute intermediate values efficiently
"""

MOD = 998244353


def qow(x, y):
    # Fast exponentiation with modulo
    res = 1
    while y > 0:
        if y % 2 == 1:
            res = res * x % MOD
        x = x * x % MOD
        y = y // 2
    return res


# Precompute Stirling numbers of the second kind s[i][j]
# s[i][j] = number of ways to partition a set of i elements into j non-empty subsets
s = [[0] * 2020 for _ in range(2020)]
s[1][1] = 1
for i in range(2, 2020):
    for j in range(1, i + 1):
        s[i][j] = (s[i - 1][j - 1] + j * s[i - 1][j]) % MOD

T = int(input())
for _ in range(T):
    n, m, k = map(int, input().split())
    ans = 0
    x = m - m // 2  # number of odd numbers in each bag (m//2 even, m - m//2 odd)
    inv = qow(m, MOD - 2)  # modular inverse of m
    # K = x * (m^(n-1)) * n
    K = x * qow(m, n - 1) % MOD * n % MOD
    for i in range(1, min(n, k) + 1):
        # Accumulate contribution: s[k][i] * K
        ans = (ans + s[k][i] * K) % MOD
        if i < min(n, k):
            # Update K for next iteration
            K = K * x % MOD * inv % MOD * (n - i) % MOD
    print(ans)


# https://github.com/VaHiX/CodeForces/