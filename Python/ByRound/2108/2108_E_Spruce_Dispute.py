# Contest 2108, Problem E: Spruce Dispute
# URL: https://codeforces.com/contest/2108/problem/E

import sys
from collections import deque


def solve():
    input = sys.stdin.readline
    t = int(input().strip())
    for _ in range(t):
        # read number of vertices
        n = int(input().strip())
        # build adjacency list for the tree
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

        # Step 1: find the centroid of the tree (unique since n is odd).
        # We'll compute subtree sizes and the size of the largest component after removing each node.
        parent = [-1] * n
        order = []
        stack = [0]
        parent[0] = -2  # mark root's parent specially
        # DFS traversal (iterative) to record an order of nodes and parents.
        while stack:
            u = stack.pop()
            order.append(u)
            for v in g[u]:
                if v != parent[u]:
                    parent[v] = u
                    stack.append(v)
        # Compute subtree sizes in reverse order and the maximum component size if node removed.
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
        # Choose node with minimal maximum component size.
        for i in range(n):
            if max_comp[i] < max_comp[centroid]:
                centroid = i

        # Step 2: BFS to find depths and parents from the centroid
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

        # Step 3: choose the leaf closest to the centroid (smallest depth).
        best = -1
        best_depth = 10**9
        for v in range(n):
            if v != centroid and len(g[v]) == 1:  # leaf
                if depth[v] < best_depth:
                    best_depth = depth[v]
                    best = v

        neighbor = parent2[best]  # this is the leaf's parent from the BFS

        # Step 4: assign colors via an iterative DFS starting from centroid
        half = n // 2  # number of colors (n is odd, half = (n-1)//2)
        color = [0] * n  # color array
        color_counter = 0
        # We'll do a pre-order traversal to assign colors (mod half)
        stack = [(centroid, -1, 0)]  # (current node, parent node, next neighbor index)
        while stack:
            u, p, i = stack.pop()
            if i == 0:
                # assign color to this node
                color[u] = (color_counter % half) + 1
                color_counter += 1
            if i < len(g[u]):
                v = g[u][i]
                # schedule the next neighbor for later
                stack.append((u, p, i + 1))
                # process child
                if v != p:
                    stack.append((v, u, 0))

        # Step 5: decide which vertex to remove (the one with larger index)
        if best > neighbor:
            bbest = best
        else:
            bbest = neighbor

        # put the removed vertex to color 0 and give centroid its color
        removed_color = color[bbest]
        color[centroid] = removed_color
        color[bbest] = 0

        # Output the edge to remove (sorted)
        u_out = best + 1
        v_out = neighbor + 1
        if u_out > v_out:
            u_out, v_out = v_out, u_out
        print(u_out, v_out)
        # Output the coloring
        print(" ".join(str(x) for x in color))


if __name__ == "__main__":
    solve()
