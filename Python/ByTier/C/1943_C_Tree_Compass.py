# Problem: CF 1943 C - Tree Compass
# https://codeforces.com/contest/1943/problem/C

"""
Algorithm: Tree Diameter and Center-based Coloring Strategy
Approach:
1. First BFS to find the diameter of the tree by finding the farthest node from an arbitrary node (root).
2. Second BFS from one end of the diameter to find the other end and compute the diameter.
3. Determine the center(s) of the diameter:
   - If diameter is even, use the middle node.
   - If diameter is odd, use two middle nodes.
4. Construct operations to color all nodes efficiently using the center(s) and distances.

Time Complexity: O(n) for each test case due to BFS traversal
Space Complexity: O(n) for storing adjacency list, parent, and distance arrays

This solution ensures that all nodes in the tree are colored black using a minimal number of operations,
which is at most the diameter of the tree.
"""

import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def solve(N, edge):
    # First BFS to find the farthest node from node 0
    parent = [-1] * N
    deq = deque([0])
    dep = [0] * N
    while deq:
        v = deq.popleft()
        for nv in edge[v]:
            if nv == parent[v]:
                continue
            parent[nv] = v
            dep[nv] = dep[v] + 1
            deq.append(nv)
    M0 = max(dep)
    root = dep.index(M0)

    # Second BFS to find the diameter by starting from the furthest node
    parent = [-1] * N
    deq = deque([root])
    dep = [0] * N
    while deq:
        v = deq.popleft()
        for nv in edge[v]:
            if nv == parent[v]:
                continue
            parent[nv] = v
            dep[nv] = dep[v] + 1
            deq.append(nv)
    dia = max(dep)
    e0, e1 = root, dep.index(dia)

    # Reconstruct the diameter path
    dia_path = [e1]
    while dia_path[-1] != e0:
        dia_path.append(parent[dia_path[-1]])

    # Based on the diameter length, determine how to place operations
    if dia & 1 == 0:
        # Even diameter: use the single center node
        mid = dia_path[dia // 2]
        res = [(mid + 1, d) for d in range(dia // 2 + 1)]
        print(len(res))
        for v, d in res:
            print(v, d)
    else:
        # Odd diameter: need two centers or handle special case
        check = (dia + 1) // 2
        if check & 1:
            # Odd number of steps needed from center toward ends
            mid = dia_path[(dia) // 2]
            res = [(mid + 1, d) for d in range((dia + 1) // 2 + 1)]
            print(len(res))
            for v, d in res:
                print(v, d)
        else:
            # Even number steps, use both middle nodes
            mid0, mid1 = dia_path[(dia) // 2], dia_path[(dia + 1) // 2]
            res = [(mid0 + 1, d) for d in range(1, (dia + 1) // 2, 2)] + [
                (mid1 + 1, d) for d in range(1, (dia + 1) // 2, 2)
            ]
            print(len(res))
            for v, d in res:
                print(v, d)


for _ in range(int(input())):
    N = int(input())
    edge = [[] for v in range(N)]
    for i in range(N - 1):
        u, v = mi()
        edge[u - 1].append(v - 1)
        edge[v - 1].append(u - 1)

    solve(N, edge)


# https://github.com/VaHiX/CodeForces/