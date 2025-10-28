# Problem: CF 1700 A - Optimal Path
# https://codeforces.com/contest/1700/problem/A

# Flowerbox
"""
Problem: Find minimum cost path from (1,1) to (n,m) in an n x m grid.
Grid value at (i,j) is (i-1)*m + j.
Turtle can only move right or down.
Algorithm: Mathematical optimization approach based on optimal path structure.
Time Complexity: O(1) per test case
Space Complexity: O(1)
"""

for i in [*open(0)][1:]:
    n, m = map(int, i.split())
    # Formula derived from optimal path analysis:
    # Path must go right (m-1) steps and down (n-1) steps
    # Minimum cost is calculated using arithmetic progression sum
    print(m * (m - 1 + n * n + n) // 2)


# https://github.com/VaHiX/codeForces/