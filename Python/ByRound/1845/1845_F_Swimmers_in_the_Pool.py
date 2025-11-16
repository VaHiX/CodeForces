# Problem: CF 1845 F - Swimmers in the Pool
# https://codeforces.com/contest/1845/problem/F

"""
Algorithm: Number Theoretic Transform (NTT) + Inclusion-Exclusion Principle

Purpose:
This code calculates the number of meeting moments among swimmers in a pool.
Each swimmer swims back and forth between points 0 and l with constant speed.
We need to find how many times at least two swimmers are at the same point in the pool during the time t.

Approach:
1. Use NTT to efficiently compute convolution of swimmer positions.
2. Identify points where at least two swimmers meet using convolution results.
3. Apply inclusion-exclusion principle to count actual meeting moments within [0, t].

Time Complexity: O(n log n + M log M), where M = max speed * 2
Space Complexity: O(M), for arrays used in NTT and for storing intermediate results.

Where:
- n is the number of swimmers
- l is the pool length
- t is the duration of the process
- M = max speed * 2

"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


mod = 998244353
G = 3
r = [pow(3, mod >> i, mod) for i in range(23)]
ir = [pow(i, mod - 2, mod) for i in r]


def ntt(A, N, sgn=1):
    L = N.bit_length() - 1
    rev = [0] * N
    for i in range(N):
        j = rev[i] = (rev[i >> 1] >> 1) | (i & 1) * (N >> 1)
        if i < j:
            A[i], A[j] = A[j], A[i]
    for i in range(L):
        a = 1 << i
        step = r[i + 1] if sgn == 1 else ir[i + 1]
        for j in range(0, N, a * 2):
            w = 1
            for k in range(j, j + a):
                x, y = A[k], A[k + a] * w % mod
                A[k], A[k + a] = (x + y) % mod, (x - y) % mod
                w = w * step % mod
    if sgn == -1:
        inv = pow(N, -1, mod)
        for i, x in enumerate(A):
            A[i] = x * inv % mod


l, t = LII()
n = II()
A = LII()
m = max(A)
N = 1 << (m * 2 + 1).bit_length()
f = [0] * N
B, B2 = [0] * N, [0] * N
for a in A:
    B[a] = 1
    B2[m - a] = 1
ntt(B, N)
ntt(B2, N)
C = [b * b for b in B]
C2 = [b * b2 for b, b2 in zip(B, B2)]
ntt(C, N, -1)
ntt(C2, N, -1)
for a in A:
    C[a * 2] -= 1
for i in range(1, N):
    if C[i] or (i + m < N and C2[i + m]):
        f[i] = 1
h = [[] for _ in range(N)]
for i in range(1, N):
    for j in range(i * 2, N, i):
        h[j].append(i)
for i in range(N - 1, 0, -1):
    if f[i]:
        for j in h[i]:
            f[j] = 1

mod = 10**9 + 7
res = 0
g = [0] * N
for i in range(1, N):
    if f[i]:
        g[i] = (t * i) // (2 * l)
        for j in h[i]:
            g[i] -= g[j]
            g[i] %= mod
        res += g[i]
        res %= mod
print(res)


# https://github.com/VaHiX/CodeForces/