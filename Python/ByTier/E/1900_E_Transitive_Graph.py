# Problem: CF 1900 E - Transitive Graph
# https://codeforces.com/contest/1900/problem/E

"""
Algorithm: Transitive Graph with SCC and Topological Sort
Purpose: Find the longest simple path in a transitive graph and among all such paths, 
         return the one with the smallest value.

Techniques Used:
- Kosaraju's algorithm for finding strongly connected components (SCCs)
- Topological sorting of condensed graph
- Dynamic programming on DAG to compute longest path with minimum value

Time Complexity: O(n + m)
Space Complexity: O(n + m)

Where n is the number of vertices and m is the number of edges.
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
        index += 2
        a = list(map(int, data[index : index + n]))
        index += n
        graph = [[] for _ in range(n + 1)]  # Original adjacency list
        rev_graph = [[] for _ in range(n + 1)]  # Reverse adjacency list
        for _ in range(m):
            u = int(data[index])
            v = int(data[index + 1])
            index += 2
            graph[u].append(v)
            rev_graph[v].append(u)
        visited = [False] * (n + 1)
        order = []
        ptr = [0] * (n + 1)
        stack = []
        # First DFS to get finishing order
        for i in range(1, n + 1):
            if not visited[i]:
                visited[i] = True
                stack.append(i)
                while stack:
                    u = stack[-1]
                    if ptr[u] < len(graph[u]):
                        v = graph[u][ptr[u]]
                        ptr[u] += 1
                        if not visited[v]:
                            visited[v] = True
                            stack.append(v)
                    else:
                        stack.pop()
                        order.append(u)
        visited2 = [False] * (n + 1)
        comp = [0] * (n + 1)
        comp_index = 0
        ptr2 = [0] * (n + 1)
        # Second DFS to find SCCs
        for i in range(len(order) - 1, -1, -1):
            node = order[i]
            if not visited2[node]:
                comp_index += 1
                stack2 = [node]
                visited2[node] = True
                comp[node] = comp_index
                while stack2:
                    u = stack2[-1]
                    if ptr2[u] < len(rev_graph[u]):
                        v = rev_graph[u][ptr2[u]]
                        ptr2[u] += 1
                        if not visited2[v]:
                            visited2[v] = True
                            comp[v] = comp_index
                            stack2.append(v)
                    else:
                        stack2.pop()
        num_sccs = comp_index
        comp_size = [0] * (num_sccs + 1)
        comp_sum = [0] * (num_sccs + 1)
        # Calculate size and sum of each SCC
        for i in range(1, n + 1):
            c = comp[i]
            comp_size[c] += 1
            comp_sum[c] += a[i - 1]
        # Build condensed graph
        cond_edges = set()
        for u in range(1, n + 1):
            for v in graph[u]:
                cu = comp[u]
                cv = comp[v]
                if cu != cv:
                    cond_edges.add((cu, cv))
        adj_cond = [[] for _ in range(num_sccs + 1)]
        pred = [[] for _ in range(num_sccs + 1)]
        in_degree = [0] * (num_sccs + 1)
        for u, v in cond_edges:
            adj_cond[u].append(v)
            pred[v].append(u)
            in_degree[v] += 1
        q = deque()
        for i in range(1, num_sccs + 1):
            if in_degree[i] == 0:
                q.append(i)
        topo = []
        # Topological sort of condensed graph
        while q:
            u = q.popleft()
            topo.append(u)
            for v in adj_cond[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    q.append(v)
        dp_len = [0] * (num_sccs + 1)
        dp_val = [0] * (num_sccs + 1)
        best_len = 0
        best_val = 0
        # DP on topological order to compute longest path with min value
        for u in topo:
            dp_len[u] = comp_size[u]
            dp_val[u] = comp_sum[u]
            for v in pred[u]:
                cand_len = dp_len[v] + comp_size[u]
                cand_val = dp_val[v] + comp_sum[u]
                if cand_len > dp_len[u] or (
                    cand_len == dp_len[u] and cand_val < dp_val[u]
                ):
                    dp_len[u] = cand_len
                    dp_val[u] = cand_val
            if dp_len[u] > best_len or (dp_len[u] == best_len and dp_val[u] < best_val):
                best_len = dp_len[u]
                best_val = dp_val[u]
        results.append(f"{best_len} {best_val}")
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/