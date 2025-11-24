# Problem: CF 1857 G - Counting Graphs
# https://codeforces.com/contest/1857/problem/G

"""
Code Purpose:
This code solves the problem of counting the number of different graphs that satisfy specific conditions:
1. The graph has exactly one minimum spanning tree (MST).
2. The given tree is the unique MST of the graph.
3. Edge weights are integers not exceeding S.
4. No self-loops or multiple edges.

The approach is based on the following idea:
- For each edge in the MST, we determine the valid weight range that ensures it remains part of any MST.
- For non-MST edges, we count how many weights can be assigned so that they do not form a smaller weight edge that would contradict the MST property.
- Using Union-Find (Disjoint Set Union) to efficiently manage connected components during the process.

Time Complexity: O(n * log n) per test case, due to sorting and Union-Find operations.
Space Complexity: O(n) for storing parent and size arrays and edge list.
"""

mod = 998244353
import sys


def solve():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        S = int(data[index])
        index += 1
        edges = []
        for i in range(n - 1):
            u = int(data[index])
            v = int(data[index + 1])
            w = int(data[index + 2])
            index += 3
            edges.append((w, u, v))
        edges.sort(key=lambda x: x[0])  # Sort edges by weight
        parent = list(range(n))  # Union-Find parent array
        size = [1] * n  # Size of each component

        def find(x):
            # Path compression for Union-Find
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        ans = 1  # Initialize result
        for w, u, v in edges:
            u = u - 1  # Convert to 0-based indexing
            v = v - 1
            ru = find(u)
            rv = find(v)
            if ru == rv:
                # Edge connects same component, skip (already in MST)
                continue
            # Number of non-MST edges that can be added between two components
            count = size[ru] * size[rv] - 1
            # Valid weight range for non-MST edges: [w+1, S]
            # So number of valid weights = S - w
            factor = S - w + 1
            # For each such non-MST edge, we can choose factor possible weights
            # And we have count such edges
            ans = (ans * pow(factor, count, mod)) % mod
            # Merge components
            if size[ru] < size[rv]:
                parent[ru] = rv
                size[rv] += size[ru]
            else:
                parent[rv] = ru
                size[ru] += size[rv]
        results.append(str(ans))
    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/