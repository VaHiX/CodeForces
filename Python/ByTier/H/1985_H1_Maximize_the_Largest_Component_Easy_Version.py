# Problem: CF 1985 H1 - Maximize the Largest Component (Easy Version)
# https://codeforces.com/contest/1985/problem/H1

"""
Algorithm: 
- For each connected component of '#' cells, we calculate the bounding box (min_row, max_row, min_col, max_col)
- We use a 2D difference array technique to efficiently track how many cells each row/column would contribute to after setting all cells in a row/column to '#'.
- For each row or column, we compute the maximum possible size of a connected component when that row/column is set to '#'.
- The time and space complexity is determined by the grid size n*m.

Time Complexity: O(n * m)
Space Complexity: O(n * m)
"""

from collections import deque
from sys import stdin, stdout

input = lambda: stdin.readline().rstrip()
print = lambda *x, sep=" ", end="\n": stdout.write(sep.join(map(str, x)) + end)


def valid(i, j):
    # Check if coordinates (i, j) are within bounds
    if 0 <= i < n and 0 <= j < m:
        return True
    else:
        return False


def bfs(a, b):
    # Perform BFS to find the size and bounding box of a connected component
    global min_row, max_row, min_col, max_col, cnt
    que = deque()
    min_row = float("inf")
    min_col = float("inf")
    max_row = float("-inf")
    max_col = float("-inf")
    cnt = 0
    que.appendleft((a, b))
    v_a[a][b] = 1
    while que:
        x, y = que.pop()
        cnt += 1
        min_row = min(x, min_row)
        min_col = min(y, min_col)
        max_row = max(x, max_row)
        max_col = max(y, max_col)
        for j0, j1 in steps:
            # Check if adjacent cell is valid, unvisited, and is '#'
            if (
                valid(x + j0, y + j1)
                and v_a[x + j0][y + j1] == 0
                and l[x + j0][y + j1] == "#"
            ):
                que.appendleft((x + j0, y + j1))
                v_a[x + j0][y + j1] = 1


def solve():
    global v_a, steps, n, m, l
    n, m = map(int, input().split())
    l = [input() for i in range(n)]
    if m == 1:
        # If only one column, we can set the entire column to '#' and get n cells
        print(n)
        return
    elif n == 1:
        # If only one row, we can set the entire row to '#' and get m cells
        print(m)
        return
    steps = [[0, -1], [-1, 0], [0, 1], [1, 0]]
    v_a = [[0] * m for i in range(n)]
    row = [0] * n
    col = [0] * m
    dot_cnt_row = [0] * n
    dot_cnt_col = [0] * m

    # Count dots in each row and column
    for i in range(n):
        for j in range(m):
            if l[i][j] == ".":
                dot_cnt_row[i] += 1
                dot_cnt_col[j] += 1
            if not v_a[i][j] and l[i][j] == "#":
                bfs(i, j)
                # Update difference array
                row[max(min_row - 1, 0)] += cnt
                col[max(min_col - 1, 0)] += cnt
                if max_row + 2 < n:
                    row[max_row + 2] -= cnt
                if max_col + 2 < m:
                    col[max_col + 2] -= cnt

    # Compute prefix sums and find maximum
    ans = max(row[0] + dot_cnt_row[0], col[0] + dot_cnt_col[0])
    for i in range(1, max(n, m)):
        if i < n:
            row[i] += row[i - 1]
            ans = max(ans, row[i] + dot_cnt_row[i])
        if i < m:
            col[i] += col[i - 1]
            ans = max(ans, col[i] + dot_cnt_col[i])
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/