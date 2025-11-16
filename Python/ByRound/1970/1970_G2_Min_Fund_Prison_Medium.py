# Problem: CF 1970 G2 - Min-Fund Prison (Medium)
# https://codeforces.com/contest/1970/problem/G2

"""
Code Purpose:
This code solves the problem of dividing a prison (represented as a graph) into exactly two complexes (connected components),
with exactly one corridor connecting them. The goal is to minimize the total funding required, which includes:
1. Funding for the complexes: k^2 for each complex of size k
2. Funding for building new corridors: c per corridor

Approach:
1. First, find all connected components in the original graph.
2. Use dynamic programming to determine which subset sizes of components can be combined into one complex.
3. For each possible split of components, compute the minimum cost of splitting into two complexes and building required corridors.
4. Also, consider building one additional corridor between two nodes that are in different components.
5. Return the minimum cost found or -1 if impossible.

Algorithms:
- Graph traversal (DFS) to find connected components
- Dynamic Programming to check combinations of component sizes
- BFS to compute connected components after removing an edge

Time Complexity:
O(n^2 + m) for each test case, where n is number of nodes and m is number of edges.

Space Complexity:
O(n + m) for storage of graph representation and auxiliary arrays.
"""

import sys
from collections import deque


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        m = int(data[index + 1])
        c_val = int(data[index + 2])
        index += 3
        edges = []
        graph_full = [[] for _ in range(n + 1)]
        for i in range(m):
            u = int(data[index])
            v = int(data[index + 1])
            index += 2
            edges.append((u, v))
            graph_full[u].append(v)
            graph_full[v].append(u)

        # Find connected components using DFS
        comp_list = []
        visited_full = [False] * (n + 1)
        for i in range(1, n + 1):
            if not visited_full[i]:
                stack = [i]
                visited_full[i] = True
                cnt = 0
                while stack:
                    node = stack.pop()
                    cnt += 1
                    for neighbor in graph_full[node]:
                        if not visited_full[neighbor]:
                            visited_full[neighbor] = True
                            stack.append(neighbor)
                comp_list.append(cnt)
        total_comp = len(comp_list)

        # Dynamic Programming to check valid splits (subset sum)
        dp2 = [False] * (n + 1)
        dp2[0] = True
        for size in comp_list:
            for j in range(n, size - 1, -1):
                if dp2[j - size]:
                    dp2[j] = True

        best_ans = float("inf")

        # Check all possible splits of components into two complexes
        for j in range(1, n):
            if dp2[j]:
                cost_candidate = j * j + (n - j) * (n - j) + c_val * (total_comp - 1)
                if cost_candidate < best_ans:
                    best_ans = cost_candidate

        # Build adjacency list for base graph
        base_adj = [[] for _ in range(n + 1)]
        for u, v in edges:
            base_adj[u].append(v)
            base_adj[v].append(u)

        # Try removing each existing edge and see if it creates valid split
        for idx in range(m):
            u, v = edges[idx]
            adj = [lst[:] for lst in base_adj]
            # Remove the current edge from the graph
            if v in adj[u]:
                adj[u].remove(v)
            if u in adj[v]:
                adj[v].remove(u)

            # Find connected components after removing the edge
            visited_edge = [False] * (n + 1)
            comp_id_arr = [-1] * (n + 1)
            comp_sizes = []
            comp_index = 0

            for i in range(1, n + 1):
                if not visited_edge[i]:
                    queue = deque([i])
                    visited_edge[i] = True
                    comp_nodes = []
                    while queue:
                        node = queue.popleft()
                        comp_nodes.append(node)
                        for neighbor in adj[node]:
                            if not visited_edge[neighbor]:
                                visited_edge[neighbor] = True
                                queue.append(neighbor)
                    comp_sizes.append(len(comp_nodes))
                    for node in comp_nodes:
                        comp_id_arr[node] = comp_index
                    comp_index += 1

            # If the two endpoints are still in same component, skip
            if comp_id_arr[u] == comp_id_arr[v]:
                continue

            a = comp_sizes[comp_id_arr[u]]
            b = comp_sizes[comp_id_arr[v]]
            other_sizes = []
            for i in range(len(comp_sizes)):
                if i != comp_id_arr[u] and i != comp_id_arr[v]:
                    other_sizes.append(comp_sizes[i])

            total_other = sum(other_sizes)
            dp = [False] * (total_other + 1)
            dp[0] = True
            for sz in other_sizes:
                for j in range(total_other, sz - 1, -1):
                    if dp[j - sz]:
                        dp[j] = True

            # Try different allocations of remaining components
            for j in range(0, total_other + 1):
                if dp[j]:
                    x = a + j
                    cost_candidate = (
                        x * x + (n - x) * (n - x) + c_val * len(other_sizes)
                    )
                    if cost_candidate < best_ans:
                        best_ans = cost_candidate

        if best_ans == float("inf"):
            results.append("-1")
        else:
            results.append(str(best_ans))

    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/