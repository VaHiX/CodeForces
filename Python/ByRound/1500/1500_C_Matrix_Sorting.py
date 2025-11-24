# Problem: CF 1500 C - Matrix Sorting
# https://codeforces.com/contest/1500/problem/C

"""
Matrix Sorting Problem

Algorithm:
- This problem involves transforming matrix A into matrix B using sorting operations on columns.
- We model this as a topological sorting problem on a directed graph where nodes represent columns.
- The key insight is to determine if the rows of B can be achieved by sorting columns of A in some order.
- We use a topological sort approach:
  1. For each column, we create a dependency graph based on the relative order of elements in B.
  2. We build a graph where an edge from column i to column j means that sorting on column i must happen before column j.
  3. Perform topological sort to determine the order of columns to sort.
  4. Apply these sorts to A and check if we get B.

Time Complexity: O(n * m^2 + n^2 * m) in the worst case
Space Complexity: O(n * m)

"""

n, m = [int(t) for t in input().split()]
a = [[int(t) for t in input().split()] for _ in range(n)]
b = [[int(t) for t in input().split()] for _ in range(n)]

# Initialize data structures for graph building
inc = []  # inc[i] stores whether column i has any dependency (order constraint)
brick = []  # brick[i] stores row indices where column i has decreasing values

# For each column, track order constraints and decreasing positions
for x in range(m):
    z = []  # List of 1s and 0s indicating if next element is smaller
    w = []  # List of row indices where element decreases
    for y in range(n - 1):
        # If next value is smaller, mark a constraint
        if b[y + 1][x] < b[y][x]:
            z.append(1)
        else:
            z.append(0)
        # If elements differ, note row index for later processing
        if b[y + 1][x] ^ b[y][x]:  # XOR, true if values are different
            w.append(y)
    inc.append(z)
    brick.append(w)

# Calculate out-degree of each column
S = [sum(r) for r in inc]  # S[i] counts how many dependencies column i has
v = [0] * n  # visited array for tracking row processing

col = []  # Store the topologically sorted order of columns
stack = [i for i in range(m) if S[i] == 0]  # Start with columns having no dependencies

# Perform topological sort
while stack:
    g = stack.pop()  # Get column with no more dependencies
    col.append(g)  # Add to result order
    # For each row where column g has a change
    for e in brick[g]:
        if v[e]:  # Skip if already processed
            continue
        v[e] = 1  # Mark row as processed
        # Check all columns for dependencies on this row
        for x in range(m):
            if inc[x][e]:  # If column x depends on row e
                S[x] -= 1  # Reduce dependency count
                if S[x] == 0:  # If no more dependencies
                    stack.append(x)  # Add to processing queue

# Apply the column sorts in reverse order (topological sort)
for e in reversed(col):
    a.sort(key=lambda x: x[e])

# Check if transformation succeeded
if a == b:
    print(len(col))
    print(*[e + 1 for e in reversed(col)])  # Output 1-indexed column numbers
else:
    print(-1)  # Transformation impossible


# https://github.com/VaHiX/CodeForces/