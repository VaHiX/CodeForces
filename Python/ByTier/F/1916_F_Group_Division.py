# Problem: CF 1916 F - Group Division
# https://codeforces.com/contest/1916/problem/F

"""
Algorithm: Graph Partitioning using DFS and Biconnected Components
Approach:
- This is a graph partitioning problem where we need to divide nodes into two groups such that:
  1. Each group has exactly n1 and n2 nodes respectively
  2. All nodes in each group are connected (directly or indirectly)
- The solution uses a greedy approach combined with biconnected component analysis:
  - Initially assign one node to group 1 (computer science) and others to group 0 (mathematics)
  - Iteratively move nodes from group 0 to group 1 if they form a leaf in the current subgraph
  - For more complex cases, use DFS-based biconnected component analysis with lowlink values
  - Move nodes to group 1 if they are articulation points or bridges in the current graph

Time Complexity: O(N * M) where N = N1 + N2 and M is number of edges
Space Complexity: O(N + M) for storing the graph and auxiliary arrays
"""

import random
import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def solve(N0, N1, M, edge):
    # Initialize group assignment: 1 for computer science group, 0 for mathematics group
    group = [1] * (N0 + N1)
    group[0] = 0  # Start by putting node 0 in mathematics group

    def connection_check():
        # Check if all nodes in group 0 are reachable from each other
        visit = [False] * (N0 + N1)
        root = [group.index(p) for p in range(2)]  # Find roots of each group
        for p in range(2):
            visit[root[p]] = True
            stack = [root[p]]
            while stack:
                v = stack.pop()
                for nv in edge[v]:
                    if group[nv] == p and not visit[nv]:
                        visit[nv] = True
                        stack.append(nv)
        return all(a for a in visit)

    # Try to assign remaining nodes in mathematics group
    for _ in range(N1 - 1):

        leaf = False
        # Look for leaf nodes (degree 1) that can be moved to mathematics group
        for v in range(N0 + N1):
            if group[v] == 1:
                check = 0
                for nv in edge[v]:
                    if group[nv] == 1:
                        check += 1
                if check == 1:
                    group[v] = 0
                    leaf = True
                    break
        if leaf:
            # If we found a leaf, continue to next iteration
            continue

        # If no leaf found, use DFS approach for biconnected analysis
        parent = [-1] * (N0 + N1)
        lowlink = [-1] * (N0 + N1)
        v_ord = [-1] * (N0 + N1)
        child = [0] * (N0 + N1)
        tree_edge = [[] for v in range(N0 + N1)]

        def calc_lowlink(start):
            # DFS to calculate lowlink values for biconnected components
            stack = [(start, -1)]
            nxt_ord = 0
            visited = []
            while stack:
                v, pv = stack.pop()
                if v < 0:
                    # Backtracking phase
                    v = ~v
                    lowlink[v] = v_ord[v]
                    for nv in edge[v]:
                        if nv == parent[v]:
                            continue
                        if group[nv] == 0:
                            continue
                        if v_ord[nv] > v_ord[v]:
                            # Forward edge
                            lowlink[v] = min(lowlink[v], lowlink[nv], v_ord[nv])
                        else:
                            # Back edge
                            lowlink[v] = min(lowlink[v], v_ord[nv])
                    continue

                if v_ord[v] != -1:
                    continue
                # First visit
                if pv != -1:
                    child[pv] += 1
                    parent[v] = pv
                    tree_edge[pv].append(v)
                v_ord[v] = nxt_ord
                visited.append(v)
                nxt_ord += 1
                stack.append((~v, -1))
                for nv in edge[v]:
                    if group[nv] == 0:
                        continue
                    stack.append((nv, v))

        root = group.index(1)  # Root of computer science group
        calc_lowlink(root)

        # Identify articulation points and move them to mathematics group
        for v in range(N0 + N1):
            if group[v] == 0:
                continue

            joint = False

            # Check if current node is an articulation point
            if v == root:
                if child[v]:
                    joint = True
            else:
                for nv in tree_edge[v]:
                    if nv == parent[v]:
                        continue
                    if group[nv] == 1 and lowlink[nv] >= v_ord[v]:
                        joint = True

            if joint:
                continue

            # If not articulation point, try to move node to mathematics group
            flg = False
            for nv in edge[v]:
                if group[nv] == 0:
                    group[v] = 0
                    flg = True

            if flg:
                break

    # Prepare output arrays 
    A = [v + 1 for v in range(N0 + N1) if group[v] == 1]  # Computer science group
    B = [v + 1 for v in range(N0 + N1) if group[v] == 0]  # Mathematics group

    assert len(B) == N1  # Ensure correct size for mathematics group

    print(*A)
    print(*B)


def make_random_graph(N0, N1, M):
    N = N0 + N1
    edge = set([(i, i + 1) for i in range(N - 1)] + [(0, N - 1)])
    while len(edge) < M:
        u = random.randint(0, N - 1)
        v = random.randint(0, N - 1)
        if u != v:
            edge.add((min(u, v), max(u, v)))

    res_edge = [[] for v in range(N)]
    for u, v in edge:
        res_edge[u].append(v)
        res_edge[v].append(u)

    return res_edge


for _ in range(int(input())):
    N0, N1, M = mi()

    edge = [[] for v in range(N0 + N1)]
    for i in range(M):
        u, v = mi()
        u, v = u - 1, v - 1
        edge[u].append(v)
        edge[v].append(u)

    solve(N0, N1, M, edge)


# https://github.com/VaHiX/CodeForces/