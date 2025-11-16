# Problem: CF 1789 F - Serval and Brain Power
# https://codeforces.com/contest/1789/problem/F

"""
Algorithm: Find the longest powerful subsequence in a string.
A powerful subsequence is one that can be split into k repetitions (k >= 2) of a base string.

Approach:
1. Use dynamic programming to compute LCS (Longest Common Subsequence) between parts of the string.
2. Try different splits of the string into 2 or 3 parts.
3. For each split, compute how many times the subsequences can be repeated.
4. Also use a greedy approach to build potential repeating patterns and check their length.

Time Complexity: O(n^4) where n is the length of the string.
Space Complexity: O(n^3) for the 3D DP array used in lcs3.
"""

def lcs(a, b):
    # Create a 2D DP table for LCS
    v = [[-1] * (len(a) + 1) for _ in range(len(b) + 1)]
    for i in range(len(a) + 1):
        v[0][i] = 0  # Base case
    for i in range(len(b) + 1):
        v[i][0] = 0  # Base case
    for x in range(len(a)):
        for y in range(len(b)):
            if a[x] == b[y]:
                v[y + 1][x + 1] = v[y][x] + 1
            else:
                v[y + 1][x + 1] = max(v[y][x + 1], v[y + 1][x])
    return v[len(b)][len(a)]


def lcs3(a, b, c):
    # Create a 3D DP table for LCS of 3 strings
    v = [[[-1] * (1 + len(a)) for _ in range(1 + len(b))] for _ in range(1 + len(c))]
    for i in range(len(a) + 1):
        v[0][0][i] = 0  # Base case
    for i in range(len(b) + 1):
        v[0][i][0] = 0  # Base case
    for i in range(len(c) + 1):
        v[i][0][0] = 0  # Base case

    for x in range(len(a)):
        for y in range(len(b)):
            for z in range(len(c)):
                if a[x] == b[y] == c[z]:
                    v[z + 1][y + 1][x + 1] = v[z][y][x] + 1
                else:
                    v[z + 1][y + 1][x + 1] = max(
                        v[z][y + 1][x + 1], v[z + 1][y + 1][x], v[z + 1][y][x + 1]
                    )
    return v[-1][-1][-1]


def check(s, t):
    # Calculate how many full repetitions of t can be formed from s
    i = 0
    for e in s:
        if e == t[i % len(t)]:
            i += 1
    return i // len(t)


s = input()

n = len(s)
best = 0
# Try splitting into 2 parts and compute max LCS*2
for t in range(1, n):
    best = max(best, 2 * lcs(s[:t], s[t:]))
# Try splitting into 3 parts and compute max LCS*3
for t in range(1, n):
    for tt in range(t + 1, n):
        if min(t, tt - t, n - tt) < best // 3:
            continue  # Early termination for performance
        best = max(best, 3 * lcs3(s[:t], s[t:tt], s[tt:]))

# Greedy approach to construct longest repeating patterns
bests = [""]
alph = [chr(ord("a") + i) for i in range(26)]
it = 0
while bests:
    it += 1
    nbests = []
    for t in bests:
        for c in alph:
            w = t + c
            v = check(s, w)
            if v >= 2:
                best = max(v * it, best)
            if v >= 5:
                nbests.append(w)
    bests = nbests
print(best)


# https://github.com/VaHiX/CodeForces/