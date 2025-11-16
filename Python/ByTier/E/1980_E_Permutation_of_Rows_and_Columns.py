# Problem: CF 1980 E - Permutation of Rows and Columns
# https://codeforces.com/contest/1980/problem/E

"""
Purpose: Determine if matrix 'a' can be transformed into matrix 'b' using row and column swaps.
Algorithm: 
    1. For each element in matrix 'b', store its row and column position in arrays p and q.
    2. For each row in 'a', compute the corresponding row in 'b' by finding the row of the first element of that row in matrix 'b'.
    3. For each column in 'a', compute the corresponding column in 'b' by finding the column of the first element of that column in matrix 'b'.
    4. Use these mappings to verify if the transformation is possible by checking if for every element in matrix 'a', 
       its position in the transformed matrix matches the corresponding element in matrix 'b'.

Time Complexity: O(n * m)
Space Complexity: O(n * m)
"""

import sys

rl = sys.stdin.buffer.readline

t = int(rl())
for _ in range(t):
    m, n = map(int, rl().split())
    a = [[*map(int, rl().split())] for _ in range(m)]
    b = [[*map(int, rl().split())] for _ in range(m)]
    r, p = [0] * m, [0] * (m * n + 1)  # r: row mapping, p: position of element in b
    c, q = [0] * n, [0] * (m * n + 1)  # c: column mapping, q: position of element in b
    for i in range(m):
        for j in range(n):
            p[b[i][j]], q[b[i][j]] = i, j  # Store row and column of each element in b
    for i in range(m):
        r[i] = p[a[i][0]]  # Map row i in a to row in b based on first element in row
    for j in range(n):
        c[j] = q[a[0][j]]  # Map column j in a to column in b based on first element in column
    ans = "YES"
    for i in range(m):
        for j in range(n):
            if a[i][j] != b[r[i]][c[j]]:  # Check if the mapped positions match
                ans = "NO"
    print(ans)


# https://github.com/VaHiX/CodeForces/