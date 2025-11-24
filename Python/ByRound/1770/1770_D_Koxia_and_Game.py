# Problem: CF 1770 D - Koxia and Game
# https://codeforces.com/contest/1770/problem/D

"""
Algorithm: Graph Connectivity + Cycle Detection + Modular Arithmetic
Time Complexity: O(n) per test case (amortized due to union-find like traversal)
Space Complexity: O(n) for adjacency list and visited array

This solution models the game as a graph where each round corresponds to an edge
between elements of arrays a and b. The goal is to count valid arrays c such that
the resulting multiset sequences form a permutation. This is determined by examining
connected components of the graph formed by these edges.

The key idea is to detect cycles and determine if the structure allows for a valid
choice of c that ensures Koxia's win. For each connected component:
- If it's a tree (no cycles), there are 2 choices for each edge.
- If it's a cycle, we must check if the configuration allows for exactly one
  "loop" to be formed in the graph.
- If there are more than one loop or configurations are inconsistent, answer is 0.

Uses DFS to traverse connected components and counts edges and vertices to verify
structure compatibility with required properties.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]

mod = 998244353

def solve():
    n = int(input())
    a = list(map(lambda x: int(x) - 1, input().split()))  # Convert to 0-indexed
    b = list(map(lambda x: int(x) - 1, input().split()))  # Convert to 0-indexed
    
    # Build adjacency list for the graph
    edge = [[] for i in range(n)]
    for i in range(n):
        edge[a[i]].append(b[i])
        if a[i] != b[i]:
            edge[b[i]].append(a[i])
    
    seen = [0] * n  # Track visited nodes
    ans = 1
    for i in range(n):
        if seen[i]:
            continue
        todo = [i]  # DFS stack
        cnt_e = 0  # Total edges in component
        loop = 0   # Number of self-loops (v -> v)
        cnt_v = 0  # Number of vertices in component
        seen[i] = 1
        while todo:
            v = todo.pop()
            cnt_v += 1
            for u in edge[v]:
                cnt_e += 1
                if seen[u] == 0:
                    seen[u] = 1
                    todo.append(u)
                elif u == v:
                    loop += 1
        # If there are 2 or more self-loops, no valid c exists
        if loop >= 2:
            print(0)
            return
        # If there's exactly one self-loop, then the configuration must satisfy:
        # 2 * cnt_v = cnt_e + 1 (tree with one cycle)
        if loop == 1:
            if cnt_v * 2 == cnt_e + 1:
                ans *= n  # For each such component, multiply by n possibilities
                ans %= mod
            else:
                print(0)
                return
        # If no self-loops, check if it's a valid structure:
        # 2 * cnt_v = cnt_e (for cycle in graph)
        else:
            if cnt_v * 2 == cnt_e:
                ans *= 2  # Each cycle gives 2 options
                ans %= mod
            else:
                print(0)
                return
    print(ans % mod)

for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/