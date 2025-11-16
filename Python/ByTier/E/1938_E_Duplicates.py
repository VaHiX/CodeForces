# Problem: CF 1938 E - Duplicates
# https://codeforces.com/contest/1938/problem/E

"""
Algorithm: 
This code solves a problem where we need to modify a matrix to ensure every row and column contains duplicates.
The approach identifies rows and columns that are complete (contain all values from 1 to n), which means they don't have duplicates.
We then modify entries to ensure duplicates exist in every row and column.

Key steps:
1. Identify rows and columns with no duplicates (complete sets)
2. Modify entries to create duplicates:
   - If there are complete rows, modify one entry in each row to make duplicates in that row
   - If there are complete columns, modify one entry in each column to make duplicates in that column
   - The minimum number of modifications is max(len(rows), len(cols)) - 1
   - Handle special cases for small matrices

Time Complexity: O(n^2) per test case due to iteration over all elements twice
Space Complexity: O(n) for storing row/column indices with no duplicates and intermediate sets
"""
import sys

t = int(sys.stdin.readline().strip())
for _ in range(t):
    n = int(sys.stdin.readline().strip())
    node = []
    for i in range(n):
        node.append([*map(int, sys.stdin.readline().strip().split())])
    X = []  # Stores indices of rows that are complete (all n values present)
    Y = []  # Stores indices of columns that are complete (all n values present)
    for i in range(n):
        s = set()
        for j in range(n):
            s.add(node[i][j])
        if len(s) == n:
            X.append(i)
    for j in range(n):
        s = set()
        for i in range(n):
            s.add(node[i][j])
        if len(s) == n:
            Y.append(j)
    print(max(len(X), len(Y)))
    ans = []
    # If no complete rows, make rows have duplicates
    if not X:
        if len(Y) == 1:
            # Find a value not in the column to use for modification
            k = node[0][Y[0]] % n + 1
            for j in range(n):
                if node[0][j] != node[0][Y[0]]:
                    k = node[0][j]
            ans.append((1, Y[0] + 1, k))
        else:
            # Find a value not in the first row to use for modification
            s = set()
            for j in range(n):
                s.add(node[0][j])
            k = 1
            for i in range(1, n + 1):
                if i not in s:
                    k = i
            for j in Y:
                ans.append((1, j + 1, k))
        for i in ans:
            print(*i)
        continue
    # If no complete columns, make columns have duplicates
    if not Y:
        if len(X) == 1:
            # Find a value not in the row to use for modification
            k = node[X[0]][0] % n + 1
            for i in range(n):
                if node[i][0] != node[X[0]][0]:
                    k = node[i][0]
            ans.append((X[0] + 1, 1, k))
        else:
            # Find a value not in the first column to use for modification
            s = set()
            for i in range(n):
                s.add(node[i][0])
            k = 1
            for i in range(1, n + 1):
                if i not in s:
                    k = i
            for i in X:
                ans.append((i + 1, 1, k))
        for i in ans:
            print(*i)
        continue
    # If both complete rows and columns exist, modify entries
    m = min(len(X), len(Y)) - 1
    s = []
    ans = []
    # Modify entries in both X and Y to create duplicates
    for i in range(m):
        x, y = X[i], Y[i]
        if node[x][y] < n:
            ans.append((x + 1, y + 1, n))
        else:
            ans.append((x + 1, y + 1, 1))
    # Handle remaining cases
    for i in range(m, max(len(X), len(Y))):
        x, y = X[m], Y[m]
        if i < len(X):
            x = X[i]
        if i < len(Y):
            y = Y[i]
        s.append(node[x][y])
    k = 0
    # Special handling for different sizes of s
    if len(s) == 1:
        x, y = X[m], Y[m]
        if node[x][y] < n:
            ans.append((x + 1, y + 1, n))
        else:
            ans.append((x + 1, y + 1, 1))
    if len(s) == n:
        # If all values are unique, make first entry in all rows and cols have the same value
        for i in range(n):
            x, y = X[0], Y[0]
            if i < len(X):
                x = X[i]
            if i < len(Y):
                y = Y[i]
            if node[x][y] < n:
                ans.append((x + 1, y + 1, n))
            else:
                ans.append((x + 1, y + 1, 1))
    if 1 < len(s) < n:
        # Find a missing value and assign to remaining entries
        s = set()
        for i in range(m, max(len(X), len(Y))):
            x, y = X[m], Y[m]
            if i < len(X):
                x = X[i]
            if i < len(Y):
                y = Y[i]
            s.add(node[x][y])
        k = 1
        for i in range(1, n + 1):
            if i not in s:
                k = i
        for i in range(m, max(len(X), len(Y))):
            x, y = X[m], Y[m]
            if i < len(X):
                x = X[i]
            if i < len(Y):
                y = Y[i]
            ans.append((x + 1, y + 1, k))
    for i in ans:
        print(*i)


# https://github.com/VaHiX/CodeForces/