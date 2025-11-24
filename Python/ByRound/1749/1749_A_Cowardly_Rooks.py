# Problem: CF 1749 A - Cowardly Rooks
# https://codeforces.com/contest/1749/problem/A

"""
Problem: Cowardly Rooks

Purpose:
This code determines whether it's possible to move exactly one rook on an n x n chessboard such that:
1. The rook is moved to a different cell.
2. No two rooks attack each other after the move.

Algorithm/Techniques:
- For each test case, read board size n and number of rooks m.
- Read the positions of all rooks.
- Check if it's possible to move exactly one rook such that no two rooks attack each other.
- This is equivalent to checking if there exists a valid move for at least one rook.
- If n == m, then each rook must be in a unique row and column (total of m rows/columns used).
  - In this case, no rook can be moved without attacking another because all rows/columns are occupied.
- If n > m, there are unused rows/columns, so we can move one rook to an empty row or column.

Time Complexity: O(1) - Since n and m are bounded by 8, the number of operations is constant.
Space Complexity: O(1) - Only a fixed amount of memory is used for input storage.

Input:
- First line contains t (number of test cases)
- Each test case consists of:
  - Two integers n, m (board size and rook count)
  - Next m lines contain x_i, y_i (rook positions)

Output:
- "YES" if exactly one rook can be moved to a valid position
- "NO" otherwise
"""

for _ in range(int(input())):  # Read number of test cases and loop through each
    n, m = map(int, input().split())  # Read board size n and rook count m
    for _ in range(m):  # Read all rook positions (but do not store them)
        input()
    # If n equals m, all rows/columns are occupied, so no moves possible
    # If n is greater than m, there exists at least one unused row/column for a move
    print("NO" if n == m else "YES")


# https://github.com/VaHiX/codeForces/