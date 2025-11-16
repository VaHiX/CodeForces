# Problem: CF 1921 F - Sum of Progression
# https://codeforces.com/contest/1921/problem/F

"""
Algorithm: Sum of Arithmetic Progression with Optimization
Approach:
- For each query (s, d, k), we compute a sum of form: 
  sum_{i=0}^{k-1} a[s + i*d] * (i+1)
- Uses a technique to optimize by precomputing prefix sums
- Time Complexity: O(n * sqrt(n) + q)
- Space Complexity: O(n + q)

This implementation uses a graph-based approach and prefix sum optimizations 
to efficiently compute weighted sums along arithmetic progressions.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v, w):
    # Helper function to pack three integers into one using bit operations
    return u << 40 ^ v << 20 ^ w


def make_graph(n, m):
    # Build a graph to organize queries by step size d
    s = [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        s[x[i] + 2] += 1
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]
        s[j] += 1
    return G, s


t = int(input())
ans = []
for _ in range(t):
    n, q = map(int, input().split())
    a = [0] + list(map(int, input().split()))  # 1-indexed array
    x = [0] * (2 * q)
    for i in range(q):
        s, d, k = map(int, input().split())
        x[2 * i], x[2 * i + 1] = d, f(i, s, k)  # Pack query info
    Q, s0 = make_graph(n, q)
    ans0 = [0] * q
    b, c = [0] * (n + 1), [0] * (n + 1)
    for d in range(1, n + 1):
        if s0[d + 1] - s0[d] <= d:
            # Small step size: compute each query directly
            for v in range(s0[d], s0[d + 1]):
                i, s, k = Q[v] >> 40, (Q[v] >> 20) & 0xFFFFF, Q[v] & 0xFFFFF
                ans1 = 0
                for j in range(k):
                    ans1 += a[s + d * j] * (j + 1)
                ans0[i] = ans1
        else:
            # Large step size: use prefix sums for optimization
            for i in range(1, n + 1):
                b[i] = b[max(i - d, 0)] + a[i] * (i // d + min(i % d, 1))
            for i in range(1, n + 1):
                c[i] = c[max(i - d, 0)] + a[i]
            for v in range(s0[d], s0[d + 1]):
                i, s, k = Q[v] >> 40, (Q[v] >> 20) & 0xFFFFF, Q[v] & 0xFFFFF
                ans1 = b[s + d * (k - 1)] - b[max(s - d, 0)]
                x = s // d + min(s % d, 1) - 1
                ans1 -= x * (c[s + d * (k - 1)] - c[max(s - d, 0)])
                ans0[i] = ans1
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/