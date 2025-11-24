# Problem: CF 1689 D - Lena and Matrix
# https://codeforces.com/contest/1689/problem/D

"""
Algorithm: Minimax Manhattan Distance on Grid
Approach:
- Transform the 2D grid coordinates using the change of variables: (i, j) -> (i + j, i - j)
- For each black cell (bi, bj), compute its transformed coordinates (bi + bj, bi - bj)
- Find the min and max values of both transformed coordinates
- The optimal point is the one that minimizes the maximum Manhattan distance to all black cells
- This is done by checking all possible grid points and evaluating their cost using the transformed coordinates

Time Complexity: O(n * m) per test case
Space Complexity: O(k) where k is the number of black cells
"""

import sys

input = sys.stdin.readline


T = int(input())
for iii in range(T):
    n, m = map(int, input().split())
    bi = []
    bj = []
    for i in range(n):
        x = list(input())[:-1]  # Read the line and remove the newline character
        for j in range(m):
            if x[j] == "B":
                bi.append(i + j)  # Transform x-coordinate
                bj.append(i - j)  # Transform y-coordinate
    mibi = min(bi)  # Minimum transformed x-coordinate
    mabi = max(bi)  # Maximum transformed x-coordinate
    mibj = min(bj)  # Minimum transformed y-coordinate
    mabj = max(bj)  # Maximum transformed y-coordinate

    def f(i, j):
        # Transform current cell coordinates
        x = i + j
        y = i - j
        # Calculate maximum distance to black cells using transformed coordinates
        res = max(abs(mabi - x), abs(mibi - x), abs(mabj - y), abs(mibj - y))
        return res

    ai, aj = -1, -1
    ans = 10**10
    for i in range(n):
        for j in range(m):
            if ans > f(i, j):
                ans = f(i, j)
                ai, aj = i, j
    print(ai + 1, aj + 1)  # Output 1-indexed coordinates


# https://github.com/VaHiX/CodeForces/