# Problem: CF 1680 F - Lenient Vertex Cover
# https://codeforces.com/contest/1680/problem/F

"""
Algorithm: Lenient Vertex Cover using DFS and Tree Decomposition
Time Complexity: O(n + m) per testcase
Space Complexity: O(n + m) per testcase

This solution uses a DFS-based approach to find a lenient vertex cover.
It builds a DFS tree and tracks back edges to detect odd cycles.
The algorithm handles cases where a standard vertex cover might not be
possible by considering the possibility of inverting a subtree to satisfy
the "at most one edge with both endpoints in the set" constraint.

The approach works by:
1. Building a DFS tree of the graph
2. Identifying back edges and their impact on coloring
3. Checking if the graph can be covered with at most one "double" edge
4. Using a transformation to fix cases where a solution exists but needs subtree inversion
"""

input = __import__("sys").stdin.readline


DFS_IN = 0
DFS_OUT = 1


def solve():
    n, m = map(int, input().split())

    adj = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(lambda x: int(x) - 1, input().split())
        adj[u].append(v)
        adj[v].append(u)

    cnt_odd = 0
    dfs_in = [0] * n
    dfs_out = [0] * n
    depth = [0] * n + [-1]
    color = [-1] * n + [1]
    removed_back_edge = None
    dp = [[0] * 2 for _ in range(n + 1)]

    i = 0
    stack = [(0, -1, DFS_IN)]
    while len(stack) > 0:
        i += 1
        u, par, state = stack.pop()
        if state == DFS_IN:
            if color[u] != -1:
                continue

            dfs_in[u] = i
            color[u] = color[par] ^ 1
            depth[u] = depth[par] + 1
            stack.append((u, par, DFS_OUT))
            for v in adj[u]:
                if color[v] == -1:
                    stack.append((v, u, DFS_IN))
                elif depth[v] - depth[u] not in (-1, 1) and depth[u] > depth[v]:

                    if color[u] == color[v]:
                        if removed_back_edge is None:
                            removed_back_edge = (u, v)
                        else:
                            removed_back_edge = (n, n)

                    parity = color[u] ^ color[v] ^ 1
                    dp[u][parity] += 1
                    dp[v][parity] -= 1
                    cnt_odd += parity

        if state == DFS_OUT:
            dfs_out[u] = i

            dp[par][0] += dp[u][0]
            dp[par][1] += dp[u][1]

    color.pop()

    if removed_back_edge is None or removed_back_edge != (n, n):

        xor = (
            1
            if removed_back_edge is not None
            and (color[removed_back_edge[0]], color[removed_back_edge[1]]) == (0, 0)
            else 0
        )
        print("YES")
        print("".join(str(x ^ xor) for x in color))
        return

    invert_node = next(
        (u for u in range(1, n) if dp[u][1] == cnt_odd and dp[u][0] == 0), None
    )
    if invert_node is None:
        print("NO")
        return

    xor = color[invert_node]
    xor_subtree = lambda u: dfs_in[invert_node] <= dfs_in[u] <= dfs_out[invert_node]
    print("YES")
    print(
        "".join(
            str(x ^ (1 if xor_subtree(u) else 0) ^ xor) for u, x in enumerate(color)
        )
    )


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/