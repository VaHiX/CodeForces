# Problem: CF 2163 E - Plegma
# https://codeforces.com/contest/2163/problem/E

"""
Problem: E. Plegma
This is a run-twice (communication) problem where two players (A and B) must communicate
the connectivity of a binary grid through a strategy agreed upon before the second run.

The grid G has n rows and n columns with values 0 or 1. Connectivity is defined as whether
there exists a path of 1s connecting all 1-cells, moving only in four directions (left, right, up, down).

Strategy:
- Player A inspects the full grid and determines row r and column c to send to Player B
- Player B receives the r-th row and c-th column, and must reconstruct the connectivity
- The trick is to use "extreme" positions (first or last column/row with a 1) to infer connectivity

Algorithms:
1. Player A analysis:
   - For each row, store number of 1s and the index of the leftmost 1
   - For each column, store number of 1s and the index of the topmost 1
   - If connectivity is 1, ensure the row/column with the minimal left/top position is chosen
   - If connectivity is 0, ensure the row/column with the maximal left/top position is chosen

2. Player B reconstruction:
   - If row has more 1s than column -> connectivity is 0
   - If row has fewer 1s than column -> connectivity is 1
   - If same number of 1s, check first 1 position in row vs column:
     - If row's first 1 is at or before column's first 1 -> connectivity 1
     - Otherwise -> connectivity 0

Time Complexity: O(n^2) - for reading grid, scanning each row/column once to compute stats
Space Complexity: O(n^2) - for storing the grid and auxiliary arrays
"""

import sys

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def tt():
    sys.stdout.flush()


def sd():
    print("Yes")


def df():
    print("No")


s = input()[:-1]
if s[0] == "f":
    for __ in range(fg()):
        n, C = fgh()
        a = []
        for i in range(n):
            s = input()[:-1]
            b = []
            for j in range(n):
                if s[j] == "1":
                    b.append(1)
                else:
                    b.append(0)
            a.append(b[:])
        z1 = []  # list of (number_of_ones, leftmost_1_index, row_index) for each row
        z2 = []  # list of (number_of_ones, topmost_1_index, col_index) for each column
        for i in range(n):
            f = n  # initialize to n (beyond grid)
            x = 0
            for j in range(n):
                if a[i][j]:
                    f = min(f, j)  # track leftmost 1 in row i
                x += a[i][j]
            z1.append((x, f, i))
        for j in range(n):
            f = n  # initialize to n (beyond grid)
            x = 0
            for i in range(n):
                if a[i][j]:
                    f = min(f, i)  # track topmost 1 in column j
                x += a[i][j]
            z2.append((x, f, j))
        if C:
            # For connectivity 1, choose row with minimum leftmost 1 and column with maximum topmost 1
            print(min(z1)[2] + 1, max(z2)[2] + 1)
        else:
            # For connectivity 0, choose row with maximum leftmost 1 and column with minimum topmost 1
            print(max(z1)[2] + 1, min(z2)[2] + 1)
else:
    for _ in range(fg()):
        n = fg()
        s1 = input()[:-1]  # received row
        s2 = input()[:-1]  # received column
        if s1.count("1") > s2.count("1"):
            # If row has more 1s than column, connectivity must be 0
            print(0)
            continue
        if s1.count("1") < s2.count("1"):
            # If row has fewer 1s than column, connectivity must be 1
            print(1)
            continue
        if s1.find("1") <= s2.find("1"):
            # If first 1 in row is at or before first 1 in column, connectivity is 1
            print(1)
            continue
        # Otherwise, connectivity is 0
        print(0)


# https://github.com/VaHiX/CodeForces/