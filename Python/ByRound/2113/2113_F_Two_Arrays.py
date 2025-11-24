# Problem: CF 2113 F - Two Arrays
# https://codeforces.com/contest/2113/problem/F

"""
F. Two Arrays

Purpose:
This problem aims to maximize the sum of distinct elements in two arrays, a and b,
by swapping elements at the same indices. At each index i, we can choose to swap a[i] with b[i].

Approach:
1. We model this as a graph coloring problem where nodes represent numbers in [1, 2*n].
2. For every index i, there's an edge between a[i] and b[i]. We try to color these edges such that
   each number gets one of two colors (representing which array it ends up in).
3. A number with both edges colored the same way will contribute 1 to total distinct count.
4. The algorithm uses BFS-like propagation to assign colors to numbers to maximize distinct counts.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithms/Techniques:
- Graph coloring
- BFS-style traversal with two-passes for handling inconsistent assignments
"""

max2 = lambda x, y: x if x > y else y
min2 = lambda x, y: y if x > y else x
from sys import stdin

input = lambda: stdin.readline().rstrip()
ls = lambda: map(int, input().split())
ln = lambda: int(input())
lnums = lambda: list(map(int, input().split()))


def slv():
    n = ln()
    a, b = lnums(), lnums()
    f = [0] * (2 * n + 1)  # color array to track assignment for each number: 0=None, 1=Array A, 2=Array B, 3=Conflict
    g = [0] * n            # visited indices in current pass

    def upd(x, t):
        # Update the color of number x with type t (1 or 2)
        if f[x] == 0:
            f[x] = t
        elif f[x] == 3 - t:  # conflict between different types
            f[x] = 3

    pos = [[] for i in range(2 * n + 1)]  # positions where each number appears
    vis = [0] * (2 * n + 1)               # visited numbers for traversal

    # Build adjacency list from the pairings
    for i, (x, y) in enumerate(zip(a, b)):
        pos[x].append(i)
        pos[y].append(i)

    q = list(range(n))
    tmp = []

    # First BFS pass to assign colors greedily, handling possible edge cases
    while q:
        i = q.pop()
        if g[i]:
            continue
        g[i] = 1
        x, y = a[i], b[i]

        # If numbers are equal or both already set to conflicting color (3)
        if x == y or f[x] == f[y] == 3:
            f[x] = 3
        elif (f[x] == 3 and f[y] == 0) or (f[x] == 0 and f[y] == 3):
            # Delay processing to resolve later
            tmp.append(i)
            g[i] = 0
            continue
        elif f[x] == 1 or f[y] == 2:
            # Swap pair to ensure valid coloring
            a[i], b[i] = y, x
            upd(x, 2)
            upd(y, 1)
        else:
            # Normal update color
            upd(x, 1)
            upd(y, 2)

        # Traverse neighbors if not already visited
        if not vis[x]:
            q.extend(pos[x])
            vis[x] = 1
        if not vis[y]:
            q.extend(pos[y])
            vis[y] = 1

    # Second pass to handle delayed nodes
    q = tmp
    while q:
        i = q.pop()
        if g[i]:
            continue
        g[i] = 1
        x, y = a[i], b[i]

        if x == y or f[x] == f[y] == 3:
            f[x] = 3
        elif f[x] == 1 or f[y] == 2:
            a[i], b[i] = y, x
            upd(x, 2)
            upd(y, 1)
        else:
            upd(x, 1)
            upd(y, 2)

        if not vis[x]:
            q.extend(pos[x])
            vis[x] = 1
        if not vis[y]:
            q.extend(pos[y])
            vis[y] = 1

    # Count number of distinct elements using f values:
    z = 0
    for x in f:
        z += (x + 1) >> 1  # This effectively counts how many numbers belong to either array
    print(z)
    print(*a)
    print(*b)
    return


for ii in range(ln()):
    a = slv()


# https://github.com/VaHiX/codeForces/