# Problem: CF 1137 A - Skyscrapers
# https://codeforces.com/contest/1137/problem/A

"""
A. Skyscrapers
Algorithm: For each cell in the grid, compute the minimum possible maximum height
           by considering both row and column orderings.
Techniques:
    - Sorting and mapping to assign ranks
    - Preprocessing rows and columns independently
    - Combining row and column constraints

Time Complexity: O(n * m * log(min(n,m)))
Space Complexity: O(n * m)

Given a grid of skyscraper heights, for each intersection (i,j):
1. Compute the minimum rank needed to preserve ordering in row i
2. Compute the minimum rank needed to preserve ordering in column j
3. Take max of both to get required maximum height
4. Add 1 to convert from 0-based to 1-based indexing

The problem asks for the minimal x such that we can assign values from [1,x] 
to all skyscrapers on row i and column j, preserving their relative order.
"""

import sys

input = lambda: sys.stdin.readline().strip()


def init():
    n, m = map(int, input().split())
    grid = [[int(s) for s in input().split()] for _ in range(n)]
    return n, m, grid


def solve(n: int, m: int, grid: list[list[int]]) -> list[str]:
    smaller = [[0] * m for _ in range(n)]  # For each cell, how many smaller elements are there
    larger = [[0] * m for _ in range(n)]   # For each cell, how many larger elements are there
    # Process rows: compute rank-based constraints
    for i in range(n):
        row = sorted(set(grid[i]))  # Unique values in the row, sorted
        k = len(row)
        d = {v: i for i, v in enumerate(row)}  # Map value to its rank
        for j in range(m):
            smaller[i][j] = d[grid[i][j]]      # Rank of current element in row
            larger[i][j] = k - 1 - d[grid[i][j]]  # Number of larger elements in row
    
    # Process columns: compute rank-based constraints
    for j in range(m):
        col = sorted({grid[i][j] for i in range(n)})  # Unique values in the column, sorted
        k = len(col)
        d = {v: i for i, v in enumerate(col)}  # Map value to its rank
        for i in range(n):
            smaller[i][j] = max(smaller[i][j], d[grid[i][j]])  # Combine row constraint with column constraint
            larger[i][j] = max(larger[i][j], k - 1 - d[grid[i][j]])  # Combine row constraint with column constraint

    # Combine constraints: the final result is sum of both + 1 (for 1-based indexing)
    for i in range(n):
        for j in range(m):
            smaller[i][j] += larger[i][j] + 1
    
    return [" ".join(map(str, r)) for r in smaller]


if __name__ == "__main__":
    args = init()
    ans = solve(*args)
    print(*ans, sep="\n")


# https://github.com/VaHiX/codeForces/