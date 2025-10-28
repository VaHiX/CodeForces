# Problem: CF 1924 E - Paper Cutting Again
# https://codeforces.com/contest/1924/problem/E

"""
E. Paper Cutting Again

Algorithm:
The problem involves computing the expected number of cuts required to reduce the area of a paper sheet to less than k.
We use the linearity of expectation and dynamic programming concepts to calculate the expected number of steps.

Key ideas:
- For each possible vertical cut (x = 1 to w-1) or horizontal cut (y = 1 to h-1), we simulate how it affects the area.
- We maintain a running sum of inverse probabilities (using precomputed modular inverses) for the expected value.
- The final result is computed as a modular fraction, requiring inversion using modular arithmetic.

Time Complexity:
O(N) where N is the maximum value of n or m, due to precomputation of inverses.

Space Complexity:
O(N) for storing precomputed inverse values.

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def cmb(n, r, mod):
    if r < 0 or r > n:
        return 0
    return (g1[n] * g2[r] % mod) * g2[n - r] % mod


mod = 10**9 + 7
N = 2 * 10**6
inverse = [1] * (N + 1)
for i in range(2, N + 1):
    inverse[i] = (-inverse[mod % i] * (mod // i)) % mod
inverse[0] = 0


def solve(n, m, k):
    if n * m < k:
        return 0
    res = 1
    for i in range(1, n):
        if i * m < k:
            continue
        tmp = i + min(m - 1, (k - 1) // i)
        res += inverse[tmp]
        res %= mod
    for j in range(1, m):
        if j * n < k:
            continue
        tmp = j + min(n - 1, (k - 1) // j)
        res += inverse[tmp]
        res %= mod
    return res


for _ in range(int(input())):
    n, m, k = mi()
    print(solve(n, m, k))


# https://github.com/VaHiX/CodeForces/