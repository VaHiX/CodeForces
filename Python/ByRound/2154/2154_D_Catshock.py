# Problem: CF 2154 D - Catshock
# https://codeforces.com/contest/2154/problem/D

"""
Purpose: 
This code solves the Catshock problem where a cat needs to reach node n from node 1 on a tree,
following a sequence of instructions. The instructions are:
1. Move to any adjacent node (if possible)
2. Destroy a node and all its adjacent edges (if not on the node)

The algorithm ensures the cat always reaches the target node n regardless of the choices it makes during move instructions.

Approach:
1. Build the tree from input
2. Perform BFS to calculate distances from node 1 to all nodes
3. Identify all leaves (degree <= 1) except the target node n
4. Process leaves in a specific order ensuring that at each step, we destroy a leaf such that:
   - The cat is at an even distance (0-based) from node 1 (based on parity)
   - This controls which moves the cat makes
5. The destruction order ensures that the cat cannot get stuck and must eventually reach node n

Time Complexity: O(n) - Each node is processed at most once in BFS and in the destruction queue
Space Complexity: O(n) - For storing adjacency list, distances, degrees and the destruction queue
"""

import sys
from collections import defaultdict, deque

INF = float("inf")
MOD = 10**9 + 7
I = lambda: list(map(int, input().split()))
MAP = lambda: map(int, input().split())
SI = lambda: list(input().strip())
input = sys.stdin.readline
sys.setrecursionlimit(10000)
aux = []

prime = 2
move = "1"
burn = "2"
for _ in range(int(input())):
    (N,) = I()
    graph = defaultdict(list)
    degree = [0] * (N + 69)

    for i in range(N - 1):
        u, v = MAP()
        graph[v].append(u)
        graph[u].append(v)

    for node in graph:
        degree[node] = len(graph[node])

    d = []
    for i in range(N + 69):
        d.append(-1)
    Q = deque()
    Q.append(1)
    ans, tmp = [], 0
    d[1], ln = 0, 1
    while ln > 0:
        curr = Q.popleft()
        ln -= 1
        for nxt in graph[curr]:
            if d[nxt] == -1:
                d[nxt] = d[curr] + 1
                ln += 1
                Q.append(nxt)
    ops = 0
    Q = deque()
    for i in range(1, N + 1):
        if i != N and degree[i] <= 1:
            Q.append(i)

    burnt = [False] * (N + 69)
    while Q:
        room = Q.popleft()
        if not burnt[room]:
            col = d[room] % 2
            cat = tmp % 2
            if col == cat:
                ans.append(move)
                ops += 1
                tmp += 1
            st = burn + " " + str(room)
            ans.append(st)
            ops += 1
            burnt[room] = True
            p = -1
            for v in graph[room]:
                if not burnt[v]:
                    p = v
                    break
            if p != -1:
                degree[p] -= 1
                if degree[p] == 1 and p != N:
                    Q.append(p)

            ans.append(move)
            ops += 1
            tmp += 1

    ops = len(ans)
    print(ops)
    print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/