# Problem: CF 1684 C - Column Swapping
# https://codeforces.com/contest/1684/problem/C

"""
Column Swapping
Problem: Determine if swapping two columns in a grid can make it "good" (each row sorted in non-decreasing order).
Algorithm:
    1. Transpose the grid to work with columns as rows.
    2. Sort columns (now rows) to get the "ideal" sorted grid.
    3. Compare original transposed grid with sorted grid to find differing columns.
    4. If more than 2 columns differ, impossible; if 0 differ, swap column 1 with itself.
    5. Otherwise, output the differing column indices.
Time Complexity: O(n * m * log(m)) due to sorting columns.
Space Complexity: O(n * m) for storing the grid and transposed versions.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")


for _ in range(int(input())):
    n, m = map(int, input().split())
    g = []
    for i in range(n):
        row = list(map(int, input().split()))
        g += [row]

    # Transpose the grid to work with columns as rows
    g = list(zip(*g))
    a = sorted(g)  # Sort columns (rows in transposed grid)
    ans = []

    # Check if the sorted version is valid (each row sorted)
    for row in list(zip(*a)):
        if list(row) != sorted(row):
            print(-1)
            break

    else:
        # Find columns that differ from the sorted version
        for i in range(m):
            if g[i] != a[i]:
                ans += [i + 1]  # 1-indexed column numbers

        # If more than 2 columns differ, impossible to fix with one swap
        if len(ans) > 2:
            ans = [-1]
        # If 0 columns differ, we can swap any column with itself
        elif not ans:
            ans = [1, 1]
        print(*ans)


# https://github.com/VaHiX/CodeForces/