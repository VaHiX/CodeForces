# Problem: CF 1856 E2 - PermuTree (hard version)
# https://codeforces.com/contest/1856/problem/E2

"""
Algorithm: PermuTree Hard Version
Purpose: Find the maximum number of pairs of vertices (u,v) such that a[u] < a[lca(u,v)] < a[v] over all permutations a of length n.
Time Complexity: O(n log n) due to sorting and dynamic programming steps
Space Complexity: O(n) for storing graph, count arrays, and auxiliary variables
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m):
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        u, v = p[(i >> 1) + 2], (i >> 1) + 2
        s[u + 2] += 1
        x[i], x[i + 1] = u, v
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


n = int(input())
p = [0] * 2 + list(map(int, input().split()))
G, s0 = make_graph(n, n - 1)
cnt = [1] * (n + 1)
for i in range(n, 1, -1):
    cnt[p[i]] += cnt[i]
pow2 = [1]
l = 63
for _ in range(l - 1):
    pow2.append(2 * pow2[-1])
sp = list(pow2)
for i in range(1, l):
    sp[i] ^= sp[i - 1]
ans = 0
inf = pow(10, 9) + 1
cnt0 = [0] * (n + 1)
for i in range(1, n + 1):
    m = s0[i + 1] - s0[i]
    if m <= 1:
        continue
    elif m == 2:
        x, y = cnt[G[s0[i]]], cnt[G[s0[i] + 1]]
        ans += x * y
        continue
    elif m == 3:
        x, y, z = cnt[G[s0[i]]], cnt[G[s0[i] + 1]], cnt[G[s0[i] + 2]]
        ans += max((x + y) * z, (y + z) * x, (z + x) * y)
        continue
    u = [0] * m
    for j in range(s0[i], s0[i + 1]):
        u[j - s0[i]] = cnt[G[j]]
    u.sort()
    v = sum(u)
    if v - u[-1] <= u[-1]:
        ma = u[-1] * (v - u[-1])
    else:
        for j in u:
            cnt0[j] += 1
        m = (v // 2) // l + 1
        dp = [0] * m
        dp[0] = 1
        s = 0
        for j in u:
            if (j <= 66 and cnt0[j]) or cnt0[j] >= 123:
                c = cnt0[j] * j
                s += c
                cnt0[j] = 0
                la = [-inf] * (j + 1)
                for k in range(min(s + 1, l * m)):
                    x, y = k // l, k % l
                    if dp[x] & pow2[y]:
                        la[k % j] = k
                    elif k - la[k % j] <= c:
                        dp[x] ^= pow2[y]
            elif cnt0[j]:
                cnt0[j] -= 1
                x, y = j // l, j % l
                for k in range(min(s // l, m - 1), -1, -1):
                    if not dp[k]:
                        continue
                    dpk = dp[k]
                    if x + k < m:
                        dp[x + k] |= (dpk & sp[l - y - 1]) << y
                        if x + k + 1 < m:
                            dp[x + k + 1] |= dpk >> (l - y)
                s += j
        ma = -1
        j = m - 1
        ok = 1
        while ok and j >= 0:
            while dp[j]:
                k = dp[j].bit_length() - 1
                x = j * l + k
                if not ma < x * (v - x):
                    ok = 0
                    break
                ma = x * (v - x)
                dp[j] ^= pow2[k]
            j -= 1
    ans += ma
print(ans)


# https://github.com/VaHiX/CodeForces/