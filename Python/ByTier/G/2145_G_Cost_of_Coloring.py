# Problem: CF 2145 G - Cost of Coloring
# https://codeforces.com/contest/2145/problem/G

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n * m + k^2)
Space Complexity: O(n * m + k^2)

This solution computes the number of beautiful colorings of an n x m grid
with exactly k colors, where each color must be used at least once and
the total number of operations is minimized.

The approach involves:
1. Precomputing factorials and inverse factorials
2. Using Stirling numbers of the second kind to count surjective functions
3. Combining combinatorial choices for rows and columns with the surjection counts
4. Accumulating results over all valid combinations of row and column operations
"""

import sys

M = 998244353
n, m, k = map(int, sys.stdin.read().split())
N = n + m
if k == 1:
    out = [0] * N
    out[min(n, m)] = 1
    print(*out[min(n, m) : N])
    raise SystemExit
K = k - 1
D = N - 2
if K > D:
    print(*([0] * (N - min(n, m))))
    raise SystemExit
L = max(n, m, K)
fact = [1] * (L + 1)
ifact = [1] * (L + 1)
for i in range(1, L + 1):
    fact[i] = fact[i - 1] * i % M
ifact[L] = pow(fact[L], M - 2, M)
for i in range(L, 0, -1):
    ifact[i - 1] = ifact[i] * i % M
cn = [fact[n] * ifact[a] % M * ifact[n - a] % M for a in range(n)]
cm = [fact[m] * ifact[b] % M * ifact[m - b] % M for b in range(m)]
surj = [0] * (D + 1)
if K == 0:
    surj[0] = 1
else:
    S = [0] * (K + 1)
    S[0] = 1
    facK = fact[K]
    for d in range(1, D + 1):
        up = d if d < K else K
        for t in range(up, 0, -1):
            S[t] = (S[t - 1] + t * S[t]) % M
        S[0] = 0
        if d >= K:
            surj[d] = facK * S[K] % M
ans = [0] * (N + 1)
MOD = M
cmv = cm
sj = surj
av = ans
n0 = n
m0 = m
for a in range(n0):
    b0 = K - a
    if b0 < 0:
        b0 = 0
    if b0 >= m0:
        continue
    wa = cn[a]
    T = m0 + a - n0
    base = n0
    idx2 = m0 + a
    r1_end = T + 1
    if r1_end > m0:
        r1_end = m0
    if b0 < r1_end:
        for b in range(b0, r1_end):
            s = (wa * cmv[b]) % MOD * sj[a + b] % MOD
            i = base + b
            av[i] = (av[i] + s) % MOD
    s0 = r1_end if r1_end > b0 else b0
    if s0 < m0:
        i = idx2
        for b in range(s0, m0):
            s = (wa * cmv[b]) % MOD * sj[a + b] % MOD
            av[i] = (av[i] + s) % MOD
print(*ans[min(n, m) : N])


# https://github.com/VaHiX/CodeForces/