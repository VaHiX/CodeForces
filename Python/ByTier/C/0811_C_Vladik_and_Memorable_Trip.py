# Problem: CF 811 C - Vladik and Memorable Trip
# https://codeforces.com/contest/811/problem/C

import sys

if sys.hexversion == 50923504:
    sys.stdin = open("cfinput.txt")

RI = lambda: map(int, sys.stdin.buffer.readline().split())
RS = lambda: map(bytes.decode, sys.stdin.buffer.readline().strip().split())
RILST = lambda: list(RI())

MOD = 10**9 + 7
"""
===============================================================================
Problem: Vladik and Memorable Trip
Algorithm: Dynamic Programming with Segment Validation
Time Complexity: O(n^2) where n <= 5000
Space Complexity: O(n + max(a[i])) where max(a[i]) <= 5000

This problem requires finding a partition of an array into disjoint segments,
such that:
1. All elements going to the same city must be in the same segment.
2. Each segment's comfort is the XOR of distinct city codes in that segment.
3. The goal is to maximize the sum of all segment comforts.

We use dynamic programming where:
- f[i] represents the maximum comfort achievable for the first i elements.
- For each ending position i, we check all possible start positions j
  to form a valid segment [j, i].
- A segment [j, i] is valid if all cities in this range appear only within this segment.
- For each valid segment, we calculate its XOR value and update DP state.

The key insight is to precompute first and last occurrence of each city, 
and for each i, iterate backward from i to find valid left boundaries.
===============================================================================
"""

def solve(n, a):
    f = [0] * (n + 1)
    mx = max(a)
    first = [n] * (mx + 1)
    last = [0] * (mx + 1)
    for i, v in enumerate(a):
        first[v] = min(first[v], i)
        last[v] = i
    vis = [-1] * (mx + 1)
    for i, v in enumerate(a):
        f[i + 1] = f[i]
        ft = first[v]
        s = 0
        for j in range(i, -1, -1):
            if last[a[j]] > i:
                break
            ft = min(ft, first[a[j]])
            if vis[a[j]] != i:
                vis[a[j]] = i
                s ^= a[j]
            if j <= ft:
                f[i + 1] = max(f[i + 1], f[j] + s)

    print(f[n])


if __name__ == "__main__":
    (n,) = RI()
    a = RILST()

    solve(n, a)


# https://github.com/VaHiX/CodeForces/