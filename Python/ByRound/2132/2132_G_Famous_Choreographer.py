# Problem: CF 2132 G - Famous Choreographer
# https://codeforces.com/contest/2132/problem/G

"""
G. Famous Choreographer

Purpose:
This code solves a problem where we need to find the minimum number of additional ballerinas 
to invite so that the arrangement of movements can be made symmetric under 180-degree rotation.

Algorithms/Techniques:
- 2D Rolling Hash for efficient substring hash computation.
- Prefix and suffix hash arrays for computing submatrix hashes quickly.
- Binary search or brute-force checks for identifying possible symmetric regions.

Time Complexity: O(n * m) per test case, where n and m are dimensions of the matrix.
Space Complexity: O(n * m) for storing prefix/suffix hashes and precomputed powers.

"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
MOD = 1000000007
P = [200052709, 182747407]


def add(a, b):
    ret = a + b
    if ret >= MOD:
        return ret - MOD
    return ret


def sub(a, b):
    ret = a - b
    if ret < 0:
        return ret + MOD
    return ret


def mult(a, b):
    ret = a * b
    if ret >= 0:
        return ret % MOD
    return ret


def bin_pow(a, n):
    ret = 1
    while n > 0:
        if (n & 1) > 0:
            ret = mult(ret, a)
        a = mult(a, a)
        n >>= 1
    return ret


# Precompute inverse powers for rolling hash
BP = [bin_pow(P[0], MOD - 2), bin_pow(P[1], MOD - 2)]
pows, bpows = [[1], [1]], [[1], [1]]
for j in range(2):
    for i in range(1000000 - 1):
        pows[j].append(mult(pows[j][i], P[j]))
        bpows[j].append(mult(bpows[j][i], BP[j]))


def solve():
    n, m = map(int, input().decode().split())
    f = [input().decode() for _ in range(n)]
    hsh = [[0 for q in range(m + 2)] for w in range(n + 2)]
    bhsh = [[0 for q in range(m + 2)] for w in range(n + 2)]
    
    # Compute prefix hashes from top-left
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            cur = mult(
                (ord(f[i - 1][j - 1]) - ord("a") + 1),
                mult(pows[0][i - 1], pows[1][j - 1]),
            )
            hsh[i][j] = add(
                sub(add(hsh[i - 1][j], hsh[i][j - 1]), hsh[i - 1][j - 1]), cur
            )
    
    # Compute suffix hashes from bottom-right
    for i in range(n, 0, -1):
        for j in range(m, 0, -1):
            cur = mult(
                (ord(f[i - 1][j - 1]) - ord("a") + 1),
                mult(pows[0][n - i], pows[1][m - j]),
            )
            bhsh[i][j] = add(
                sub(add(bhsh[i + 1][j], bhsh[i][j + 1]), bhsh[i + 1][j + 1]), cur
            )

    # Check for symmetric regions using hash values
    def isp(x1, y1, x2, y2):
        h = add(
            sub(sub(hsh[x2][y2], hsh[x1 - 1][y2]), hsh[x2][y1 - 1]), hsh[x1 - 1][y1 - 1]
        )
        bh = add(
            sub(sub(bhsh[x1][y1], bhsh[x2 + 1][y1]), bhsh[x1][y2 + 1]),
            bhsh[x2 + 1][y2 + 1],
        )
        h = mult(h, mult(bpows[0][x1 - 1], bpows[1][y1 - 1]))
        bh = mult(bh, mult(bpows[0][n - x2], bpows[1][m - y2]))
        return h == bh

    mn = n * m * 4
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if isp(1, 1, i, j):
                mn = min(mn, (2 * n - i) * (2 * m - j))
            if isp(1, j, i, m):
                mn = min(mn, (2 * n - i) * (m + j - 1))
            if isp(i, 1, n, j):
                mn = min(mn, (n + i - 1) * (2 * m - j))
            if isp(i, j, n, m):
                mn = min(mn, (n + i - 1) * (m + j - 1))
    print(mn - m * n)


t = int(input().decode())
for _ in range(t):
    solve()


# https://github.com/VaHiX/codeForces/