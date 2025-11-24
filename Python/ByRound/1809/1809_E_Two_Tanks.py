# Problem: CF 1809 E - Two Tanks
# https://codeforces.com/contest/1809/problem/E

"""
Algorithm: Simulation with Dynamic Programming
Time Complexity: O((a+b+1) * n)
Space Complexity: O(a * b)

This code simulates pouring water between two tanks with given capacities and initial water volumes.
For each possible initial state (c, d), we simulate all operations and compute the final volume in the first tank.
The approach uses a dynamic programming technique where we efficiently track the change in water levels
based on the constraints of tank capacities and pour operations.
"""

import sys

input = sys.stdin.readline

n, a, b = map(int, input().split())
v = list(map(int, input().split()))
m, M = 0, 0
s = 0
for i in v:
    s += i
    m = min(m, s)
    M = max(M, s)

p = [0, 0]
ans = [[0] * (b + 1) for _ in range(a + 1)]
for i in range(a + b + 1):
    line = []
    for j in range(i + 1):
        if j <= a and i - j <= b:
            line.append(j)
    x, y = line[0], line[-1]
    start = line[0]

    for j in v:
        start = min(max(start - j, x), y)
        line[0] = start
    for j in range(1, len(line)):
        if line[j] - 1 - M < x or line[j] - m > y:

            line[j] = line[j - 1]
        else:
            line[j] = line[j - 1] + 1

    for j in range(len(line)):
        ans[p[0] + j][p[1] - j] = line[j]

    if p[1] < b:
        p[1] += 1
    else:
        p[0] += 1
for i in ans:
    print(*i)


# https://github.com/VaHiX/CodeForces/