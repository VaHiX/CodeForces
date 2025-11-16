# Problem: CF 2045 G - X Aura
# https://codeforces.com/contest/2045/problem/G

"""
Algorithms/Techniques: 
- For X=1, the problem reduces to a simple difference between start and end heights.
- For X>1, we precompute prefix sums for rows and columns to quickly compute penalties along paths.
- Detecting invalid cases (cycles with negative total penalty) for X != 1 by checking 2x2 subgrids.

Time Complexity: O(R*C + Q) for X = 1, and O(R*C + Q) for X > 1 after preprocessing.
Space Complexity: O(R*C) for storing prefix sums and grid.
"""

r, c, x = tuple(map(int, input().split()))

grid = []
for i in range(r):
    grid.append(list(map(int, list(input()))))

q = int(input())
queries = []
for i in range(q):
    queries.append(list(map(int, input().split())))


invalid = False
if x != 1:
    # Check for invalid configurations by examining all possible 2x2 cycles
    for i in range(r - 1):
        for j in range(c - 1):
            if (grid[i][j] - grid[i + 1][j]) ** x + (
                grid[i + 1][j] - grid[i + 1][j + 1]
            ) ** x + (grid[i + 1][j + 1] - grid[i][j + 1]) ** x + (
                grid[i][j + 1] - grid[i][j]
            ) ** x != 0:
                invalid = True
                break
        if invalid:
            break

if invalid:
    # If invalid, all queries return INVALID
    for i in range(q):
        print("INVALID")
elif x == 1:
    # For X=1, just return the difference of heights
    for i in queries:
        x1 = i[0] - 1
        y1 = i[1] - 1
        x2 = i[2] - 1
        y2 = i[3] - 1
        print(grid[x1][y1] - grid[x2][y2])
else:
    # Precompute prefix sums for rows and columns
    prefrows = []
    prefcols = []
    for j in range(c):
        prefrows.append([0])
        for i in range(r - 1):
            prefrows[-1].append(prefrows[-1][-1] + (grid[i][j] - grid[i + 1][j]) ** x)
    for j in range(r):
        prefcols.append([0])
        for i in range(c - 1):
            prefcols[-1].append(prefcols[-1][-1] + (grid[j][i] - grid[j][i + 1]) ** x)

    # For each query, compute the total penalty along the path using prefix sums
    for i in queries:
        y1 = i[0] - 1
        x1 = i[1] - 1
        y2 = i[2] - 1
        x2 = i[3] - 1
        print(prefrows[x2][y2] - prefrows[x2][y1] + prefcols[y1][x2] - prefcols[y1][x1])


# https://github.com/VaHiX/CodeForces/