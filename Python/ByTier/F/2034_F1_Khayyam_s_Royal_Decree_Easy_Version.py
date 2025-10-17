# Problem: CF 2034 F1 - Khayyam's Royal Decree (Easy Version)
# https://codeforces.com/contest/2034/problem/F1

"""
Algorithm: Dynamic Programming with Combinatorics
Purpose: Calculate expected value of gems in satchel after drawing from a chest with special conditions.

Time Complexity:
    - Preprocessing factorial and inverse factorial: O(N)
    - For each test case:
        - Sorting points: O(k log k)
        - Processing all points: O(k^2)
        - Final computation: O(k)
    Overall: O(N + t * k^2) where N = 400002, t is number of test cases, k <= 500.
Space Complexity:
    - Arrays for factorials and inverses: O(N)
    - Additional arrays for processing points: O(k)

Note: MOD = 998244353 (Prime), used for modular arithmetic.
"""

ans = []
MOD = 0x3B800001  # This is 998244353 in decimal
N = 400_002
fact = [1]  # Factorial array modulo MOD
for i in range(1, N):
    fact.append(fact[-1] * i % MOD)

# Precompute modular inverses of factorials
anti = [0] * N
anti[-1] = pow(fact[-1], -1, MOD)  # Modular inverse of last factorial
for i in range(N - 2, -1, -1):
    anti[i] = anti[i + 1] * (i + 1) % MOD


# Combination function C(n, k) mod MOD using precomputed factorials
def cmb(n, k):
    if not 0 <= k <= n:
        return 0
    return fact[n] * anti[n - k] * anti[k] % MOD


for _ in range(int(input())):
    n, m, k = [int(t) for t in input().split()]
    pts = [[int(t) for t in input().split()] for _ in range(k)]
    pts.sort(key=lambda x: x[0] + x[1])  # Sort points based on sum of coordinates
    v = [0] * k

    # Dynamic programming to compute contribution of each scroll condition
    for i in range(k):
        a, b = pts[i]
        S = cmb(a + b, b)  # Base count of paths reaching (a,b)
        for j in range(i):
            c, d = pts[j]
            if c <= a and d <= b:
                # Add contribution from previous state reachable to (a,b)
                S += cmb(a + b - c - d, a - c) * v[j]
        v[i] = S % MOD

    tot = 0
    # Final computation for expected value using all scroll conditions
    for i in range(k):
        a, b = pts[i]
        tot += cmb(n - a + m - b, n - a) * v[i] * (2 * (n - a) + m - b)

    tot = tot * pow(cmb(n + m, m), -1, MOD) % MOD  # Normalize by total combinations
    tot += 2 * n + m
    ans.append(tot % MOD)

for w in ans:
    print(w)


# https://github.com/VaHiX/codeForces/