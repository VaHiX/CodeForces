# Problem: CF 2002 D2 - DFS Checker (Hard Version)
# https://codeforces.com/contest/2002/problem/D2

"""
D2. DFS Checker (Hard Version)

Purpose:
This code solves a problem where given a rooted tree and a permutation of nodes,
we need to check if the permutation represents a valid Depth-First Search (DFS) order
of the tree. For each query, we swap two elements in the permutation and recheck
if it's still a valid DFS order.

Algorithms/Techniques:
- Tree representation using adjacency list with edge indexing.
- Preprocessing for DFS order validation.
- Heavy-light decomposition concept used via ancestor tracking and subtree size.
- Efficiently maintaining and checking DFS validity with swaps.
- Bit manipulation optimizations (x ^ 1) for edge traversal.

Time Complexity: O(n * log n + q * sqrt(n))
Space Complexity: O(n)

Note: This implementation uses a specific technique to precompute the valid DFS 
order checks and efficiently handles updates using swaps, leveraging heavy-light
decomposition principles in an optimized manner.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph(n, m, a):
    x, s = [0] * (2 * m), [0] * (n + 3)
    for i in range(0, 2 * m, 2):
        u, v = a[(i >> 1) + 2], (i >> 1) + 2
        s[u + 2] += 1
        x[i], x[i + 1] = u, v
    for i in range(3, n + 3):
        s[i] += s[i - 1]
    G = [0] * m
    for i in range(0, 2 * m, 2):
        j = x[i] + 1
        G[s[j]] = x[i ^ 1]  # Bitwise XOR to get reverse edge index
        s[j] += 1
    return G, s


def dfs(u, v, z, dist, a):
    while z[u] != z[v]:
        if dist[z[u]] >= dist[z[v]]:
            u = a[z[u]]
        else:
            v = a[z[v]]
    return u if dist[u] <= dist[v] else v


def solve():
    t = int(input())
    inf = pow(10, 9) + 1
    results = []
    for _ in range(t):
        n, q = map(int, input().split())
        a = [0] * 2 + list(map(int, input().split()))  # Parent array
        p = [0] + list(map(int, input().split()))      # Permutation
        G, s0 = make_graph(n, n - 1, a)
        cnt = [1] * (n + 1)   # Subtree sizes
        for i in range(n, 1, -1):  # Compute subtree sizes
            cnt[a[i]] += cnt[i]
        dist = [inf] * (n + 1)  # Distance from root
        dist[1] = 0
        for i in range(2, n + 1):
            dist[i] = dist[a[i]] + 1
        z = list(range(n + 1))   # Ancestor tracking array

        # Build z to track current path ancestors
        for i in range(1, n + 1):
            j, ma, di = i, -1, dist[i]
            for v in range(s0[i], s0[i + 1]):  # Traverse children edges
                k = G[v]
                if dist[k] >= di and ma < cnt[k]:  # Choose best child based on subtree size
                    j, ma = k, cnt[k]
            z[j] = z[i]  # Set ancestor

        ng = 0   # Counter for invalid DFS conditions
        for i in range(1, n):  # Check initial state
            if a[p[i + 1]] != dfs(p[i], p[i + 1], z, dist, a):
                ng += 1
        for _ in range(q):
            x, y = map(int, input().split())
            indices_to_check = {i for i in [x - 1, x, y - 1, y] if 0 < i < n}  # Indices involved in updates
            
            for i in indices_to_check:
                # Recalculate invalid count for affected positions
                if a[p[i + 1]] != dfs(p[i], p[i + 1], z, dist, a):
                    ng -= 1
            p[x], p[y] = p[y], p[x]
            for i in indices_to_check:
                # Update invalid count after swapping
                if a[p[i + 1]] != dfs(p[i], p[i + 1], z, dist, a):
                    ng += 1
            results.append("YES" if ng == 0 else "NO")
    sys.stdout.write("\n".join(results) + "\n")


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/