# Problem: CF 1613 F - Tree Coloring
# https://codeforces.com/contest/1613/problem/F

"""
Algorithm: Tree Dynamic Programming with Polynomial Convolution
Technique: FFT-based polynomial multiplication, heap optimization, inclusion-exclusion principle

Time Complexity: O(n log^2 n)
Space Complexity: O(n log n)

The solution uses the following key ideas:
1. For each vertex, we compute its degree (excluding the root)
2. We group vertices by their degrees
3. For each degree group, we compute a polynomial representing valid colorings
4. We combine polynomials using FFT-based convolution
5. Finally, we apply inclusion-exclusion principle using alternating signs and factorials
"""

import sys
from collections import Counter
from heapq import heapify, heappop, heappush

raw_input = sys.stdin.readline

MOD = 998244353
rev = []
roots = [0, 1]


def dft(a):
    n = len(a)
    if len(rev) != n:
        k = (n.bit_length() - 1) - 1
        rev.extend([0] * (n - len(rev)))
        for i in range(n):
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k)
    for i in range(n):
        if rev[i] < i:
            a[i], a[rev[i]] = a[rev[i]], a[i]
    if len(roots) < n:
        k = len(roots).bit_length() - 1
        roots.extend([0] * (n - len(roots)))
        while (1 << k) < n:
            e = pow(3, (MOD - 1) >> (k + 1), MOD)
            for i in range(1 << (k - 1), 1 << k):
                roots[2 * i] = roots[i]
                roots[2 * i + 1] = (roots[i] * e) % MOD
            k += 1
    k = 1
    while k < n:
        i = 0
        while i < n:
            for j in range(k):
                u = a[i + j]
                v = (a[i + j + k] * roots[k + j]) % MOD
                a[i + j] = (u + v) % MOD
                a[i + j + k] = (u - v) % MOD
            i += 2 * k
        k *= 2


def idft(a):
    n = len(a)
    a[1:] = a[1:][::-1]
    dft(a)
    inv = pow(n, MOD - 2, MOD)
    for i in range(n):
        a[i] = (a[i] * inv) % MOD


def convmod(a, b):
    if not a or not b:
        return []
    sz, tot = 1, len(a) + len(b) - 1
    while sz < tot:
        sz *= 2
    a.extend([0] * (sz - len(a)))
    b.extend([0] * (sz - len(b)))
    dft(a)
    dft(b)
    for i in range(sz):
        a[i] = (a[i] * b[i]) % MOD
    idft(a)
    return a[:tot]


def solution():
    def nCr(n, k):
        return (fact[n] * inv_fact[n - k] % MOD) * inv_fact[k] % MOD

    n = int(input())
    fact, inv, inv_fact = [[1] * 2 for _ in range(3)]
    while len(inv) <= n:
        fact.append(fact[-1] * len(inv) % MOD)
        inv.append(inv[MOD % len(inv)] * (MOD - MOD // len(inv)) % MOD)
        inv_fact.append(inv_fact[-1] * inv[-1] % MOD)
    adj = [[] for _ in range(n)]
    for _ in range(n - 1):
        x, y = list(map(int, input().strip().split()))
        x, y = x - 1, y - 1
        adj[x].append(y)
        adj[y].append(x)
    cnt = Counter()
    for i in range(n):
        if len(adj[i]) - (i > 0):
            cnt[len(adj[i]) - (i > 0)] += 1
    min_heap = [(1, [1])]
    for d, k in cnt.items():
        poly_d_k = [0] * (k + 1)
        pw = 1
        for i in range(k + 1):
            poly_d_k[i] = (nCr(k, i) * pw) % MOD
            pw = (pw * d) % MOD
        min_heap.append((len(poly_d_k), poly_d_k))
    heapify(min_heap)
    while len(min_heap) > 1:
        _, p1 = heappop(min_heap)
        _, p2 = heappop(min_heap)
        new_p = convmod(p1, p2)
        heappush(min_heap, (len(new_p), new_p))
    p = min_heap[0][1]
    result, sign = 0, 1
    for i in range(len(p)):
        result = (result + sign * p[i] * fact[n - i]) % MOD
        sign *= -1
    return result


print("%s" % solution())


# https://github.com/VaHiX/CodeForces/