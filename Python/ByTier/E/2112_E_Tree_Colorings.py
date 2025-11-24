# Problem: CF 2112 E - Tree Colorings
# https://codeforces.com/contest/2112/problem/E

"""
E. Tree Colorings

Purpose:
This code computes the minimum number of vertices in a tree that has exactly m beautiful colorings.
A beautiful coloring satisfies specific connectivity constraints between colors:
- The root must be green.
- Blue and green vertices must be connected without passing through yellow.
- Yellow and green vertices must be connected without passing through blue.

Algorithm:
The solution uses dynamic programming with memoization to calculate how many beautiful colorings
can be formed for trees of increasing sizes, building from small to larger trees. The idea is based
on constructing minimal trees that yield a given number of valid colorings by combining smaller structures.

Time Complexity: O(M * log M) where M is the maximum value in input.
Space Complexity: O(M) for storing dp arrays and auxiliary data structures.

"""

import sys

data = sys.stdin.buffer.read().split()
t = int(data[0])
ms = list(map(int, data[1:]))
M = max(ms)
INF = M + 5
dpch = [INF] * (M + 1)
dp = [INF] * (M + 1)
dpch[1] = 0  # Base case: tree with 1 vertex has 0 additional colorings beyond base

for g in range(1, M + 1):
    if dpch[g] == INF:
        continue
    dp[g] = dpch[g] + 1  # Update minimum number of nodes needed for current count of colorings
    a = g + 2
    cost = dp[g]
    lim = M // a
    for x in range(1, lim + 1):
        c = dpch[x] + cost  # Combine two structures
        m = x * a
        if c < dpch[m]:
            dpch[m] = c  # Store minimum number of nodes needed for 'm' colorings

out = []
for m in ms:
    ans = dp[m]
    out.append(str(ans if ans < INF else -1))
sys.stdout.write("\n".join(out))


# https://github.com/VaHiX/codeForces/