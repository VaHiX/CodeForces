# Problem: CF 2113 E - From Kazan with Love
# https://codeforces.com/contest/2113/problem/E

"""
E. From Kazan with Love

Purpose:
This code solves a problem where Marat (a person living in a tree-structured city) needs to find the earliest moment he can reach his workplace without meeting any of his enemies along the way. Each enemy has a fixed path from their home to work, and Marat must avoid being at the same vertex or edge as an enemy at any time step.

Algorithms:
- BFS for building parent and depth arrays for tree traversal
- Shortest path computation using Lowest Common Ancestor (LCA) technique
- Simultaneous BFS with dynamic obstacle removal to simulate safe paths for Marat

Time Complexity:
O(n * m + n * log n) where n is number of nodes and m is number of enemies. 
This includes preprocessing tree structure, computing paths, and performing BFS over time steps.

Space Complexity:
O(n + m * k), where k is the average path length between enemy home and workplace.
"""

baku = []
for _ in range(int(input())):
    n, m, start, goal = [int(t) for t in input().split()]
    start -= 1
    goal -= 1
    edges = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b = [int(t) - 1 for t in input().split()]
        edges[a].append(b)
        edges[b].append(a)
    
    # Build parent and depth using BFS
    par = [0] * n
    depth = [0] * n
    stack = [0]
    while stack:
        a = stack.pop()
        p = par[a]
        for b in edges[a]:
            if b == p:
                continue
            par[b] = a
            depth[b] = depth[a] + 1
            stack.append(b)

    # Function to compute path from one node to another using LCA
    def path(x, y):
        p = [x]
        q = [y]
        for _ in range(depth[x] - depth[y]):
            p.append(par[p[-1]])
        for _ in range(depth[y] - depth[x]):
            q.append(par[q[-1]])
        while p[-1] != q[-1]:
            p.append(par[p[-1]])
            q.append(par[q[-1]])
        return p + q[-2::-1]

    # Read all enemy routes and compute their paths
    paths = [path(*[int(t) - 1 for t in input().split()]) for _ in range(m)]
    paths.sort(key=lambda x: -len(x))
    
    # Initialize Marat's state and visited array
    v = [0] * n
    v[start] = 1
    front = {start}
    clock = 1
    tot = 1
    
    # BFS to find earliest time when goal is reachable
    while tot and not v[goal]:
        nfront = set()
        for f in front:
            for e in edges[f]:
                if v[e]:
                    continue
                v[e] = 1
                tot += 1
                nfront.add(e)
        
        # Remove visited nodes that are blocked by enemies at current time step
        for p in paths:
            if len(p) <= clock:
                break
            b = p[clock]
            if not v[b]:
                continue
            v[b] = 0
            tot -= 1
            nfront.discard(b)
            for e in edges[b]:
                if v[e]:
                    nfront.add(e)
        front = nfront
        clock += 1
    
    # Append result: time step when goal is reached, otherwise -1
    baku.append(clock if tot else -1)
print(*baku)


# https://github.com/VaHiX/codeForces/