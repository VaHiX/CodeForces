# Problem: CF 2068 D - Morse Code
# https://codeforces.com/contest/2068/problem/D

"""
Morse Code Encoding Optimization

This code solves the problem of constructing an optimal Morse code encoding for a given set of characters with specified frequencies.
The approach uses dynamic programming to find the optimal encoding scheme that minimizes the expected transmission time.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Greedy sorting of frequencies
- Reconstruction of optimal solution from DP table

Time Complexity: O(n^3) where n is the number of characters
Space Complexity: O(n^2) for the DP table and auxiliary arrays

The problem is solved by:
1. Sorting characters by frequency in descending order
2. Using dynamic programming to compute optimal encoding structures
3. Reconstructing the actual code assignments from the DP results
"""

import sys


def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    a = [0.0] * (n + 5)
    p = list(range(n + 5))
    for i in range(1, n + 1):
        a[i] = float(next(it))
        p[i] = i
    p[1 : n + 1] = sorted(p[1 : n + 1], key=lambda x: a[x], reverse=True)
    s = [0.0] * (n + 5)
    for i in range(n, 0, -1):
        s[i] = s[i + 1] + a[p[i]]
    dp = [[float("inf")] * (n + 5) for _ in range(n + 5)]
    for i in range(1, n + 1):
        for j in range(0, n - i + 1):
            if i == 1 and j == 0:
                dp[i][j] = 0.0
            else:
                best = float("inf")
                k_start = 1 if j == 0 else 0
                k_end = min(i - j, i - 1)
                for k in range(k_start, k_end + 1):
                    val = dp[i - k][k] + s[i - k - j + 1]
                    if val < best:
                        best = val
                dp[i][j] = best
    vec = []
    i = n
    j = 0
    EPS = 1e-12
    while (i != 1) or (j != 0):
        found = False
        k_start = 1 if j == 0 else 0
        k_end = min(i - j, i - 1)
        for k in range(k_start, k_end + 1):
            lhs = dp[i - k][k] + s[i - k - j + 1]
            if abs(lhs - dp[i][j]) <= EPS:
                vec.append(j)
                i -= k
                j = k
                found = True
                break
        if not found:
            raise RuntimeError("Reconstruction failed: no matching k found")
    vec.reverse()
    b = [""] * (n + 5)
    c = [""] * (n + 5)
    i = 1
    j = 0
    for k in vec:
        for o in range(i + 1, i + j + 1):
            b[o] = c[o - i]
        for o in range(1, k + 1):
            c[o] = b[i - k + o] + "-"
        for o in range(i - k + 1, i + 1):
            b[o] = b[o] + "."
        i += j
        j = k
    res = [""] * (n + 1)
    for idx in range(1, n + 1):
        res[p[idx]] = b[idx]
    out = "\n".join(res[1 : n + 1])
    print(out)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/