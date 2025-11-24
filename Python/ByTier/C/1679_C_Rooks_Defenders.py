# Problem: CF 1679 C - Rooks Defenders
# https://codeforces.com/contest/1679/problem/C

"""
Algorithm: Coordinate Compression with Binary Indexed Tree (Fenwick Tree)
Approach:
- Use two BITs (Binary Indexed Trees): one for rows and one for columns.
- Track how many rooks exist in each row and column.
- When a rook is added/removed, update the BITs accordingly.
- For query type 3, check if all rows in the range [x1, x2] are attacked or all columns in [y1, y2] are attacked.

Time Complexity: O(q * log n) where q is number of queries and n is the size of chessboard
Space Complexity: O(n) for the BITs and auxiliary arrays
"""

import sys

input = sys.stdin.readline
R = lambda: map(int, input().split())
n, m = R()
# r[x] - number of rooks in row x
# c[y] - number of rooks in column y
# tr[x] - BIT for rows (tracks how many rows have at least one rook)
# tc[y] - BIT for columns (tracks how many columns have at least one rook)
r, c, tr, tc = [0] * (n + 1), [0] * (n + 1), [0] * (n + 1), [0] * (n + 1)


def A(t, i, v):
    # Update BIT: add value v to position i and all its ancestors
    while i <= n:
        t[i] += v
        i += i & (-i)


def Q(t, i):
    # Query BIT: get sum from 1 to i
    s = 0
    while i:
        s += t[i]
        i -= i & (-i)
    return s


for _ in range(m):
    v = [*R()]
    op, x, y = v[:3]
    if op == 1:
        # Add a rook at (x, y)
        r[x] += 1
        c[y] += 1
        # If this is the first rook in row x, update BIT for rows
        if r[x] == 1:
            A(tr, x, 1)
        # If this is the first rook in column y, update BIT for columns
        if c[y] == 1:
            A(tc, y, 1)
    elif op == 2:
        # Remove a rook from (x, y)
        r[x] -= 1
        c[y] -= 1
        # If no more rooks in row x, update BIT for rows
        if r[x] == 0:
            A(tr, x, -1)
        # If no more rooks in column y, update BIT for columns
        if c[y] == 0:
            A(tc, y, -1)
    else:
        # Check if entire subrectangle is attacked
        x1, y1 = v[3:]
        # Check if all rows from x to x1 are attacked (i.e., there exists a rook in that row)
        rows_attacked = Q(tr, x1) - Q(tr, x - 1)
        # Check if all columns from y to y1 are attacked
        cols_attacked = Q(tc, y1) - Q(tc, y - 1)
        # If number of attacked rows equals range size OR number of attacked columns equals range size
        if rows_attacked == x1 - x + 1 or cols_attacked == y1 - y + 1:
            print("Yes")
        else:
            print("No")


# https://github.com/VaHiX/CodeForces/