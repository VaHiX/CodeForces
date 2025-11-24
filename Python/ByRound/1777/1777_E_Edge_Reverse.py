# Problem: CF 1777 E - Edge Reverse
# https://codeforces.com/contest/1777/problem/E

"""
Minimum Cost to Make Graph Fully Reachable

This solution finds the minimum cost to reverse edges in a directed graph so that
there exists at least one node from which all other nodes are reachable.
The cost is defined as the maximum weight of reversed edges.

Approach:
1. First check if the graph is already fully reachable from some node.
2. If not, use binary search on the edge weights to find the minimum cost.
3. For each candidate cost (edge weight), rebuild the graph with all edges of weight <= candidate
   and check reachability using BFS from each node.
4. If a valid configuration exists, update the answer.

Time Complexity: O(m * log(max_weight) * n) where m is the number of edges,
                 n is the number of nodes, and max_weight is the maximum edge weight.
Space Complexity: O(n + m) for storing the graph and auxiliary arrays.

Algorithms/Techniques:
- Binary Search on Edge Weights
- Graph Reachability using BFS
- Union-Find or Component Traversal for reachability checking
"""

from collections import defaultdict, deque
from sys import stdin, stdout

t = int(stdin.readline())

for _ in range(t):
    n, m = [int(x) for x in stdin.readline().split()]
    real_edges = []
    weights = [0]

    for bar in range(m):
        u, v, w = [int(x) for x in stdin.readline().split()]
        u -= 1
        v -= 1
        real_edges.append((u, v, w))
        weights.append(w)

    g = defaultdict(list)
    for u, v, w in real_edges:
        g[u].append(v)

    visited = [False] * (n)

    for root in range(n):
        if visited[root] == False:
            v_star = root

            queue = deque()
            queue.append(root)
            visited[root] = True

            while len(queue) > 0:
                v = queue.popleft()
                for w in g[v]:
                    if not visited[w]:
                        visited[w] = True
                        queue.append(w)

    visited = [False] * (n)
    count = 1
    queue = deque()
    queue.append(v_star)
    visited[v_star] = True

    while len(queue) > 0:
        v = queue.popleft()
        for w in g[v]:
            if not visited[w]:
                count += 1
                visited[w] = True
                queue.append(w)

    if count == n:
        stdout.write("0\n")
    else:
        weights.sort()

        lower = -1
        upper = len(weights)
        while upper - lower > 1:
            candidate = (upper + lower) // 2
            w0 = weights[candidate]

            g = defaultdict(list)
            for u, v, w in real_edges:
                g[u].append(v)
                if w <= w0:
                    g[v].append(u)

            visited = [False] * (n)

            for root in range(n):
                if visited[root] == False:
                    v_star = root

                    queue = deque()
                    queue.append(root)
                    visited[root] = True

                    while len(queue) > 0:
                        v = queue.popleft()
                        for w in g[v]:
                            if not visited[w]:
                                visited[w] = True
                                queue.append(w)

            visited = [False] * (n)
            count = 1
            queue = deque()
            queue.append(v_star)
            visited[v_star] = True

            while len(queue) > 0:
                v = queue.popleft()
                for w in g[v]:
                    if not visited[w]:
                        count += 1
                        visited[w] = True
                        queue.append(w)

            if count < n:
                lower = candidate
            else:
                upper = candidate

        if upper == len(weights):
            stdout.write("-1\n")
        else:
            stdout.write(str(weights[upper]) + "\n")


# https://github.com/VaHiX/CodeForces/