# Problem: CF 2134 F - Permutation Oddness
# https://codeforces.com/contest/2134/problem/F

"""
F. Permutation Oddness

Purpose:
This code solves the problem of counting permutations of an array with specific values,
where each permutation's "oddness" is defined as the sum of lowbit(x XOR y) for adjacent elements.
The solution uses dynamic programming and convolution techniques to compute results efficiently.

Algorithms/Techniques:
- Precomputed binomial coefficients using Pascal's triangle
- Convolution operations for combining counts of permutations with specific properties
- Dynamic Programming on permutations with different types of elements (c0, c1, c2, c3)
- Modular arithmetic to prevent overflow

Time Complexity: O(n^3) where n = c0 + c1 + c2 + c3. This is due to nested loops in conv() and solve().
Space Complexity: O(n^2) for storing the convolution results and binomial coefficients.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 1000000007
mx = 801
comb = [[1] * (i + 1) for i in range(mx)]
for i in range(mx):
    for j in range(1, i):
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod


def conv(x, y):
    # Compute convolution of two sequences representing permutations with x and y tokens
    m = x + y
    ans = [[0] * (m + 1) for _ in range(m + 1)]
    for i in range(2, m + 1):
        i2 = i // 2
        for l1, l2 in [(i2, i - i2), (i - i2, i2)]:
            if x < l1 or y < l2:
                continue
            # Multiply binomial coefficients for choosing positions for tokens
            mul = comb[x - 1][l1 - 1] * comb[y - 1][l2 - 1] % mod
            # Combine convolution results with current step
            for j in range(i):
                for k in range(m - i + 1):
                    mul2 = comb[i - 1][j] * comb[m - i][k] % mod
                    ans[j + k + 1][i - j - 1] = (
                        ans[j + k + 1][i - j - 1] + mul * mul2
                    ) % mod
    return ans


def solve():
    # Read input values for c0,c1,c2,c3
    c0, c1, c2, c3 = map(int, input().split())
    n, rcnt, bcnt = c0 + c1 + c2 + c3, c0 + c2, c1 + c3
    # Convolve token types for red (c0, c2) and blue (c1, c3)
    r = conv(c0, c2)
    b = conv(c1, c3)
    ans = [0] * (2 * n - 1)
    # Loop over all possible counts of tokens used
    for i in range(1, min(rcnt, bcnt) + 1):
        ri, bi = r[i], b[i]
        ri1 = r[i + 1] if i + 1 <= rcnt else [0] * (rcnt + 1)
        bi1 = b[i + 1] if i + 1 <= bcnt else [0] * (bcnt + 1)
        # Calculate the final contribution to the result array
        for j in range(rcnt + 1):
            for k in range(min(bcnt + 1, n - i - j)):
                res = (i + j + k) * 2
                ans[res - 1] = (ans[res - 1] + ri[j] * bi[k] * 2) % mod
                ans[res] = (ans[res] + (ri[j] * bi1[k] + ri1[j] * bi[k])) % mod
    return ans


for _ in range(int(input())):
    print(*solve())


# https://github.com/VaHiX/codeForces/