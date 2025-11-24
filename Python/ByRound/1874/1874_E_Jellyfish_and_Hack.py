# Problem: CF 1874 E - Jellyfish and Hack
# https://codeforces.com/contest/1874/problem/E

"""
Algorithm: Dynamic Programming with Matrix Exponentiation and Inclusion-Exclusion
Time Complexity: O(n^3 * log(n)) due to matrix multiplication and DP transitions
Space Complexity: O(n^2) for storing DP states and auxiliary arrays

This code calculates the number of permutations of [1,2,...,n] such that 
the quicksort function fun(P) is greater than or equal to a given limit.
The function fun(A) recursively counts the number of comparisons made 
during partitioning in quicksort, with the pivot always being the first element.
"""

import sys

data = list(map(int, sys.stdin.read().split()))
it = iter(data)
n = next(it)
K = next(it)
M = 10**9 + 7
m = n * (n + 1) // 2 + 3
if K > m:
    print(0)
    sys.exit(0)
h = [[0] * (m + 1) for _ in range(n + 1)]
v = [0] * (m + 1)
nv = [0] * (m + 1)
for x in range(1, m + 1):
    h[0][x] = 1
    v[x] = 1
nv[0] = nv[1] = 1
for x in range(2, m + 1):
    nv[x] = ((M - M // x) * nv[M % x]) % M
for x in range(1, n + 1):
    for k in range(1, m + 1):
        v[k] = v[k] * k % M
    for l in range(1, x + 1):
        hl1 = h[l - 1]
        hx_l = h[x - l]
        for k in range(1, m + 1):
            h[x][k] = (hl1[k] * hx_l[k] % M * v[k] + h[x][k]) % M
    for k in range(1, m + 1):
        h[x][k] = h[x][k] * nv[x] % M
for x in range(2, m + 1):
    nv[x] = nv[x] * nv[x - 1] % M
z = 1
for i in range(1, n + 1):
    z = z * i % M
for x in range(1, m + 1):
    k = nv[x - 1] * nv[m - x] % M
    k = k * h[n][x] % M
    k = k * z % M
    if k:
        if (m - x) & 1:
            k = (M - k) % M
    v[x] = k
f = [0] * (m + 1)
g = [0] * (m + 1)
f[0] = 1
for x in range(1, m + 1):
    d = v[x]
    for l in range(x, 0, -1):
        g[l] = (g[l] * (M - x) + g[l - 1] + d * f[l]) % M
        f[l] = (f[l] * (M - x) + f[l - 1]) % M
    g[0] = (g[0] * (M - x) + d * f[0]) % M
    f[0] = f[0] * (M - x) % M
ans = 0
for i in range(K, m + 1):
    ans = (ans + g[i]) % M
print(ans)


# https://github.com/VaHiX/CodeForces/