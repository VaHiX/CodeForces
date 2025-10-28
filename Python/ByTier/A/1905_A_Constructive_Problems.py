# Problem: CF 1905 A - Constructive Problems
# https://codeforces.com/contest/1905/problem/A

"""
Code Purpose:
This code solves the problem of finding the minimum number of cities to rebuild in a grid such that all cities can eventually be rebuilt through adjacent aid.
The approach is based on the observation that we can cover the entire grid using a checkerboard-like pattern where we place rebuild cities at positions (i, j) where (i + j) is even or odd. To minimize the count, we choose the smaller of the two possible patterns.

Algorithms/Techniques:
- Mathematical pattern recognition on grid
- Checkerboard coloring approach

Time Complexity:
O(1) - The computation involves only basic arithmetic operations and does not depend on n or m.

Space Complexity:
O(1) - Only a constant amount of extra space is used.
"""

for i in [*open(0)][1:]:
    print(max(map(int, i.split())))


# https://github.com/VaHiX/CodeForces/