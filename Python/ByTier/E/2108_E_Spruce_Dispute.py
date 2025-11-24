# Problem: CF 2108 E - Spruce Dispute
# https://codeforces.com/contest/2108/problem/E

"""
E. Spruce Dispute

Purpose:
This code solves a tree manipulation problem where we need to remove an edge from a tree,
then assign colors to vertices such that the sum of path lengths between same-colored ornaments is maximized.

Algorithm:
1. Build adjacency list representation of the tree.
2. Find centroid of the tree using DFS and subtree size calculation.
3. Perform BFS from centroid to find depth and parent relationships.
4. Identify a leaf vertex with minimum depth among leaves (this represents one end of a longest path).
5. Determine which edge should be cut based on this leaf's connection to its parent.
6. Assign colors greedily using a DFS traversal starting from the centroid, such that:
   - Vertices along the path connecting the cut point and the selected leaf are colored with 1..n//2
   - Color 0 is reserved for the removed vertex (which has no color).
7. Return the edge to remove and the resulting color assignment.

Time Complexity: O(n) per test case, as each node is visited a constant number of times.
Space Complexity: O(n) due to storing graph, parent arrays, order, size, max_comp, depth, etc., all linear in n.

"""
import sys
from collections import deque


def solve():
    input = sys.stdin.readline
    t = int(input().strip())
    for _ in range(t):
        n = int(input().strip())
        g = [[] for _ in range(n)]
        for _i in range(n - 1):
            u_str = input().strip()
            while not u_str:
                u_str = input().strip()
            u, v = map(int, u_str.split())
            u -= 1
            v -= 1
            g[u].append(v)
            g[v].append(u)
        parent = [-1] * n
        order = []
        stack = [0]
        parent[0] = -2  # Special marker to denote root
        while stack:
            u = stack.pop()
            order.append(u)
            for v in g[u]:
                if v != parent[u]:
                    parent[v] = u
                    stack.append(v)
        size = [0] * n
        max_comp = [0] * n
        for u in reversed(order):
            size[u] = 1
            max_sub = 0
            for v in g[u]:
                if v != parent[u]:
                    size[u] += size[v]
                    if size[v] > max_sub:
                        max_sub = size[v]
            max_other = n - size[u]
            max_comp[u] = max(max_sub, max_other)
        centroid = 0
        for i in range(n):
            if max_comp[i] < max_comp[centroid]:
                centroid = i
        depth = [-1] * n
        parent2 = [-1] * n
        q = deque([centroid])
        depth[centroid] = 0
        while q:
            u = q.popleft()
            for v in g[u]:
                if depth[v] == -1:
                    depth[v] = depth[u] + 1
                    parent2[v] = u
                    q.append(v)
        best = -1
        best_depth = 10**9
        for v in range(n):
            if v != centroid and len(g[v]) == 1:  # Leaf node
                if depth[v] < best_depth:
                    best_depth = depth[v]
                    best = v
        neighbor = parent2[best]
        half = n // 2
        color = [0] * n
        color_counter = 0
        stack = [(centroid, -1, 0)]
        while stack:
            u, p, i = stack.pop()
            if i == 0:
                color[u] = (color_counter % half) + 1
                color_counter += 1
            if i < len(g[u]):
                v = g[u][i]
                stack.append((u, p, i + 1))
                if v != p:
                    stack.append((v, u, 0))
        if best > neighbor:
            bbest = best
        else:
            bbest = neighbor
        removed_color = color[bbest]
        color[centroid] = removed_color
        color[bbest] = 0
        u_out = best + 1
        v_out = neighbor + 1
        if u_out > v_out:
            u_out, v_out = v_out, u_out
        print(u_out, v_out)
        print(" ".join(str(x) for x in color))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/