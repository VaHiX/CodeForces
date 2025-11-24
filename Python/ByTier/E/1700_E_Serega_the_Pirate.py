# Problem: CF 1700 E - Serega the Pirate
# https://codeforces.com/contest/1700/problem/E

"""
Code purpose: This program determines the minimum number of swaps required to make a puzzle solvable.
A puzzle is solvable if there exists a sequence visiting cells in increasing order of their values.
The algorithm works by:
1. Identifying "holes" - cells that are greater than 1 and all their neighbors have values >= current cell.
2. For each potential swap involving a hole, check if the resulting configuration is solvable.
3. Based on the checks, output 0, 1, or 2 swaps needed.

Algorithms/Techniques: 
- Graph traversal to identify solvable sequences
- Brute force checking of possible swaps for single swap cases
- Set operations for efficient hole identification and subset checks

Time Complexity: O(n^2 * m^2 * nm) in worst-case where nm can be up to 400000.
Space Complexity: O(nm) for storing the input matrix and hole positions.
"""
import itertools


def swap(ix, iy, jx, jy):
    # Swap values at positions (ix, iy) and (jx, jy)
    a[ix][iy], a[jx][jy] = a[jx][jy], a[ix][iy]


def neighbours(x, y):
    # Return all valid neighboring cells (up, down, left, right)
    u = [(x, y)]
    if x > 0:
        u.append((x - 1, y))
    if y > 0:
        u.append((x, y - 1))
    if x < n - 1:
        u.append((x + 1, y))
    if y < m - 1:
        u.append((x, y + 1))
    return u


def hole(x, y):
    # Check if cell (x, y) is a hole (greater than 1 and all neighbors are >= it)
    t = a[x][y]
    return t > 1 and all(t <= a[u][v] for u, v in neighbours(x, y))


n, m = map(int, input().split())
a = [list(map(int, input().split())) for _ in range(n)]
# Find all holes in the table
h = {(i, j) for i in range(n) for j in range(m) if hole(i, j)}
if not h:
    # No holes means puzzle is already solvable
    print(0)
    exit()
h0 = next(iter(h))  # Take one hole as reference
counter = 0
# Iterate over all neighbor positions of the reference hole
for i in neighbours(*h0):
    # For each cell in the table, check if swapping with neighbor creates a solvable state
    for j in itertools.product(range(n), range(m)):
        if j == h0:
            continue
        swap(*i, *j)  # Perform the swap
        s = neighbours(*i) + neighbours(*j)  # Get neighbors of swapped cells
        # Check if new state is valid and the set of holes is subset of updated neighbors
        counter += not any(hole(*k) for k in s) and h.issubset(s)
        swap(*i, *j)  # Undo the swap
if counter > 0:
    # One swap is sufficient
    print(1, counter)
else:
    # At least two swaps needed
    print(2)


# https://github.com/VaHiX/CodeForces/