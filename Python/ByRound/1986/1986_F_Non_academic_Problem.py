# Problem: CF 1986 F - Non-academic Problem
# https://codeforces.com/contest/1986/problem/F

"""
Algorithm: Finding the minimum number of reachable vertex pairs after removing one edge.
Technique: 
- Use Tarjan's algorithm to find articulation points and bridges in a graph.
- For each bridge, calculate the size of the two components it separates.
- The maximum number of pairs that can be made unreachable by removing a single edge is the product of the sizes of the two components.
- Subtract this from the total number of pairs to get the result.

Time Complexity: O(n + m) - Each node and edge is visited once during the DFS.
Space Complexity: O(n + m) - For adjacency list and auxiliary arrays.
"""

def solve():
    import sys

    sys.setrecursionlimit(3000000)
    input = sys.stdin.readline
    t = int(input())
    result = []
    for _ in range(t):
        n, m = map(int, input().split())
        adj = [[] for _ in range(n + 1)]
        for _ in range(m):
            u, v = map(int, input().split())
            adj[u].append(v)
            adj[v].append(u)
        visited = [False] * (n + 1)
        tin = [0] * (n + 1)
        low = [0] * (n + 1)
        sub_tree = [0] * (n + 1)
        timer, max_pr = 0, 0

        def dfs(u, parent):
            nonlocal timer, max_pr
            visited[u] = True
            tin[u] = low[u] = timer
            timer += 1
            sub_tree[u] = 1
            for v in adj[u]:
                if v == parent:
                    continue
                if not visited[v]:
                    dfs(v, u)
                    sub_tree[u] += sub_tree[v]
                    low[u] = min(low[u], low[v])
                    if low[v] > tin[u]:
                        c = sub_tree[v]
                        max_pr = max(max_pr, c * (n - c))
                else:
                    low[u] = min(low[u], tin[v])

        dfs(1, -1)
        tot_prs = (n * (n - 1)) // 2
        res = tot_prs - max_pr
        result.append(str(res))
    sys.stdout.write("\n".join(result))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/