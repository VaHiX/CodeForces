# Problem: CF 2043 E - Matrix Transformation
# https://codeforces.com/contest/2043/problem/E

"""
Code Purpose:
This code determines whether it's possible to transform matrix A into matrix B using two types of operations:
1. Bitwise AND operation on entire rows
2. Bitwise OR operation on entire columns

The solution works by analyzing each bit position independently:
- For each bit position, it checks if the transformation is possible by simulating
  the constraints imposed by the operations on rows and columns.
- It uses a greedy approach to determine which rows and columns can be "disabled"
  (set to 0 or 1 respectively) through operations, then verifies that all remaining
  active cells match the target.

Algorithms/Techniques:
- Bit Manipulation
- Graph-based greedy approach with row/column constraint simulation
- Bit-by-bit checking (20 bits for 10^9 values)

Time Complexity: O(20 * n * m) where 20 is the number of bits (max 30 bits for 10^9)
Space Complexity: O(n + m) for storing counts and active flags
"""

import sys

input = sys.stdin.readline
K = 20


def solve():
    n, m = map(int, input().split())
    A = [list(map(int, input().split())) for _ in range(n)]
    B = [list(map(int, input().split())) for _ in range(n)]

    def possible(bit):
        # Count how many elements in each row/column will become 0 or 1 after operations
        row_zero_cnt = [0] * n  # how many 0s in each row
        col_one_cnt = [0] * m   # how many 1s in each column

        # Count the required transitions for each bit
        for i in range(n):
            for j in range(m):
                if B[i][j] >> bit & 1:  # if bit at position `bit` is 1 in B
                    col_one_cnt[j] += 1
                else:  # if bit at position `bit` is 0 in B
                    row_zero_cnt[i] += 1

        # Group rows and columns by their constraints
        col_zeros = [[] for _ in range(n + 1)]  # rows where bit is 0 in B, grouped by how many 0s
        row_ones = [[] for _ in range(m + 1)]   # cols where bit is 1 in B, grouped by how many 1s

        # Fill groups with indices that meet the criteria for that row/column
        for i, cnt in enumerate(row_zero_cnt):
            row_ones[m - cnt].append(i)

        for i, cnt in enumerate(col_one_cnt):
            col_zeros[n - cnt].append(i)

        # Set up active row/column flags
        active_rows = [True] * n
        active_cols = [True] * m
        deleted_rows = 0
        deleted_cols = 0

        # Greedily eliminate rows/columns where we can't change the result
        while col_zeros[deleted_rows] or row_ones[deleted_cols]:
            # Process columns that must stay 0 (due to constraints)
            while col_zeros[deleted_rows]:
                deleted_cols += 1
                active_cols[col_zeros[deleted_rows].pop()] = False

            # Process rows that must stay 1 (due to constraints)
            while row_ones[deleted_cols]:
                deleted_rows += 1
                active_rows[row_ones[deleted_cols].pop()] = False

        # Check if any remaining cell doesn't match target
        for i in range(n):
            for j in range(m):
                if (
                    active_cols[j]
                    and active_rows[i]
                    and A[i][j] >> bit & 1 != B[i][j] >> bit & 1
                ):
                    return False

        return True

    # Check all 20 bits to ensure transformation is possible
    for b in range(K):
        if not possible(b):
            return "No"
    return "Yes"


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/