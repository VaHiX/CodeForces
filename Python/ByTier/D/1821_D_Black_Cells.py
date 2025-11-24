# Problem: CF 1821 D - Black Cells
# https://codeforces.com/contest/1821/problem/D

"""
Algorithm: Greedy + Two Pointers
Time Complexity: O(n)
Space Complexity: O(1)

The problem involves coloring cells in segments using a pointer and a shift button.
We want to find the minimum number of moves to color at least k cells.

Key insight:
- To minimize moves, we should try to maximize the number of cells we can color in one shift.
- If we can cover k cells using exactly 'i' segments, we can compute the minimal moves.
- The number of moves is composed of:
  - Moving right to reach a segment: 2 * (i + 1) for i segments
  - Using shift to color: we subtract extra cells we don't need (x = c - k)
  - Minimizing over possible segment combinations.

The algorithm proceeds by checking prefix of segments and computing minimal moves needed.
"""

import sys

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s) - 1])


def invr():
    return map(int, input().split())


for _ in range(inp()):
    n, k = invr()
    l = inlt()
    r = inlt()
    total = 0
    for i in range(n):
        total += r[i] - l[i] + 1
    if k > total:
        print(-1)
        continue
    if k == total:
        print(r[-1] + n * 2)
        continue
    ans = float("inf")
    c, p = 0, 0
    for i in range(n):
        p += l[i] == r[i]  # Count segments with single cell
        c += r[i] - l[i] + 1  # Cumulative count of cells
        if c < k:
            continue
        x = c - k  # Extra cells beyond what we need
        # Compute moves needed for current prefix of segments
        ans = min(ans, 2 * (i + 1) + r[i] - x - min(x, p))
    print(ans)


# https://github.com/VaHiX/CodeForces/