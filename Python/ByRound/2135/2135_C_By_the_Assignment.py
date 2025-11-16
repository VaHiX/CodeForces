# Problem: CF 2135 C - By the Assignment
# https://codeforces.com/contest/2135/problem/C

"""
C. By the Assignment

Algorithms/Techniques:
- Bridge detection using Tarjan's algorithm
- Connected components decomposition
- Bipartite graph checking
- XOR property of paths in graphs
- Modular arithmetic with memoization
- Union-Find / DFS traversal for connected components

Time Complexity: O(n + m) per test case, where n is number of vertices and m is number of edges.
Space Complexity: O(n + m), for graph storage and auxiliary arrays.

For an undirected connected graph of n vertices, the value of a simple path l1,l2,...,lm
is defined as v_{l1} ⊕ v_{l2} ⊕ ... ⊕ v_{lm}. A graph is balanced if all simple paths between any two vertices have the same XOR value.

The problem asks to count how many ways we can assign weights (from 0 to V-1) to missing nodes (-1) so that the resulting graph becomes balanced.
"""

import sys
from collections import deque

MOD = 998244353
sys.setrecursionlimit(1 << 25)
input = sys.stdin.readline


def solve_case():
    n, m, V = map(int, input().split())
    a = list(map(int, input().split()))
    
    # Building adjacency list representation of the graph with edge indices
    g = [[] for _ in range(n)]
    edges = []
    for i in range(m):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        g[u].append((v, i))
        g[v].append((u, i))
        edges.append((u, v))
    
    # Tarjan's algorithm for finding bridges in the graph
    tin = [-1] * n
    low = [0] * n
    timer = 0
    bridges = set()

    def dfs(u, pe):
        nonlocal timer
        tin[u] = low[u] = timer
        timer += 1
        for v, ei in g[u]:
            if ei == pe:
                continue
            if tin[v] != -1:
                # Back edge case: update low value of u
                if tin[v] < tin[u]:
                    low[u] = low[u] if low[u] < tin[v] else tin[v]
            else:
                dfs(v, ei)
                # After DFS on child v, update low[u] based on low[v]
                if low[v] < low[u]:
                    low[u] = low[v]
                # If the lowest reachable vertex from v is after u, it's a bridge
                if low[v] > tin[u]:
                    bridges.add(ei)

    dfs(0, -1)
    
    # Assign component IDs to each node using DFS avoiding bridges
    comp = [-1] * n
    cid = 0
    for i in range(n):
        if comp[i] != -1:
            continue
        stack = [i]
        comp[i] = cid
        while stack:
            u = stack.pop()
            for v, ei in g[u]:
                # Skip bridge edges
                if ei in bridges:
                    continue
                if comp[v] == -1:
                    comp[v] = cid
                    stack.append(v)
        cid += 1

    # Group nodes into components
    comp_nodes = [[] for _ in range(cid)]
    for v in range(n):
        comp_nodes[comp[v]].append(v)

    res = 1
    color = [-1] * n
    
    # Process each connected component
    for c in range(cid):
        nodes = comp_nodes[c]
        if len(nodes) == 1:
            v = nodes[0]
            # If this node is unassigned, we can choose any of V values.
            if a[v] == -1:
                res = (res * (V % MOD)) % MOD
            continue
        
        # Detect whether component is bipartite
        is_bip = True
        for start in nodes:
            if color[start] != -1:
                continue
            color[start] = 0
            dq = deque([start])
            while dq and is_bip:
                u = dq.popleft()
                for v, ei in g[u]:
                    # Skip edges that are bridges
                    if ei in bridges:
                        continue
                    # Ensure we're still within same component
                    if comp[v] != c:
                        continue
                    if color[v] == -1:
                        color[v] = color[u] ^ 1
                        dq.append(v)
                    else:
                        if color[v] == color[u]:
                            is_bip = False
                            break
            if not is_bip:
                break
        
        # If this component isn't bipartite, check compatibility of existing values
        if not is_bip:
            for v in nodes:
                if a[v] != -1 and a[v] != 0:
                    print(0)
                    return
            continue
        else:
            # Fixed value checking for this component
            fixed_val = None
            ok = True
            for v in nodes:
                if a[v] != -1:
                    if fixed_val is None:
                        fixed_val = a[v]
                    elif fixed_val != a[v]:
                        ok = False
                        break
            if not ok:
                print(0)
                return
            # If no fixed values in component and all are unassigned, V options available
            if fixed_val is None:
                res = (res * (V % MOD)) % MOD
            else:
                # Else do nothing - we're free to assign other values
                pass

    print(res % MOD)


def main():
    t = int(input().strip())
    for _ in range(t):
        solve_case()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/