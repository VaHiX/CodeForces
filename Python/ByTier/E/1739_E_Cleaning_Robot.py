# Problem: CF 1739 E - Cleaning Robot
# https://codeforces.com/contest/1739/problem/E

# Flowerbox for code purpose and complexity
"""
Code Purpose:
This code solves the "Cleaning Robot" problem where a robot moves through a 2xN grid to clean dirty cells.
The robot always moves to the closest dirty cell, but if there are multiple closest ones, it malfunctions.
We must determine the maximum number of dirty cells that can be left for the robot to clean without malfunctioning.

Approach:
- Dynamic Programming with state f[i][j] representing max number of dirty cells cleaned
  when the robot is at row j, column i.
- Two transitions are possible:
  1. Move right to next column in same row.
  2. Move to the other row at the same column, if there's a dirty cell there (with additional cost).

Time Complexity: O(n)
Space Complexity: O(n)
"""

import sys

inf = float("inf")
mod = 998244353
input = lambda: sys.stdin.readline().rstrip()
inpnm = lambda: map(int, input().split())
inparr = lambda: [int(i) for i in input().split()]
inpint = lambda: int(input())


n = inpint()
s = []
for i in range(2):
    s.append([i for i in list(input())] + ["0", "0"])

f = [[-inf] * (2) for _ in range(n + 2)]
f[0][0] = 0
for i in range(n):
    for j in range(2):
        f[i + 1][j] = max(f[i + 1][j], f[i][j] + int(s[j][i + 1]))
        if s[j ^ 1][i] == "1":
            f[min(i + 2, n)][j ^ 1] = max(
                f[min(i + 2, n)][j ^ 1],
                f[i][j] + 1 + int(s[j ^ 1][i + 1]) + int(s[j ^ 1][i + 2]),
            )
print(max(f[n][0], f[n][1]))


# https://github.com/VaHiX/CodeForces/