# Problem: CF 1882 D - Tree XOR
# https://codeforces.com/contest/1882/problem/D

"""
Algorithm: Tree XOR
Purpose: For each root of the tree, calculate the minimum cost to make all vertex values equal using subtree operations.
Techniques: 
- Tree traversal (DFS) to build parent and size arrays
- Dynamic programming on tree to compute costs
- Prefix-sum like approach to accumulate costs from root to leaves

Time Complexity: O(n) per test case, as each node and edge is visited a constant number of times.
Space Complexity: O(n) for storing graph, parent, size, delta, and add arrays.

Approach:
1. Build adjacency list for the tree.
2. Perform DFS to get parent and size information for each node.
3. Compute base cost and delta for each node based on value differences with parent.
4. Propagate the deltas to compute total cost for each possible root.
5. Output results for all roots.
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    output_lines = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a_list = list(map(int, data[index : index + n]))
        index += n
        a = [0] + a_list  # 1-indexed array
        graph = [[] for _ in range(n + 1)]
        for i in range(n - 1):
            u = int(data[index])
            v = int(data[index + 1])
            index += 2
            graph[u].append(v)
            graph[v].append(u)
        if n == 1:
            output_lines.append("0")
            continue
        parent = [0] * (n + 1)
        size = [0] * (n + 1)
        stack = [1]
        parent[1] = 0
        order = []
        while stack:
            u = stack.pop()
            order.append(u)
            for v in graph[u]:
                if v == parent[u]:
                    continue
                parent[v] = u
                stack.append(v)
        size = [1] * (n + 1)
        for i in range(len(order) - 1, -1, -1):
            u = order[i]
            if parent[u] != 0:
                size[parent[u]] += size[u]
        base = 0
        delta = [0] * (n + 1)
        for v in range(2, n + 1):
            u = parent[v]
            c_val = a[u] ^ a[v]
            base += size[v] * c_val
            delta[v] = (n - 2 * size[v]) * c_val
        add = [0] * (n + 1)
        stack = [1]
        add[1] = 0
        while stack:
            u = stack.pop()
            for v in graph[u]:
                if v == parent[u]:
                    continue
                add[v] = add[u] + delta[v]
                stack.append(v)
        res = [base + add[i] for i in range(1, n + 1)]
        output_lines.append(" ".join(map(str, res)))
    print("\n".join(output_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/