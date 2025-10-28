# Problem: CF 2127 D - Root was Built by Love, Broken by Destiny
# https://codeforces.com/contest/2127/problem/D

"""
D. Root was Built by Love, Broken by Destiny

Purpose:
This code solves a graph-based combinatorial problem where we need to count the number of valid ways to assign
houses to two sides of a river such that all bridges connect houses on opposite sides and do not cross when
drawn as straight lines.

Key algorithms and techniques used:
- Graph theory (connected components, degree analysis)
- Tree structure recognition (m == n-1 implies tree)
- Factorial computation with modular arithmetic
- Combinatorial counting using degrees and leaf nodes

Time Complexity: O(n + m) per test case, where n is number of houses and m is number of bridges.
Space Complexity: O(n + m) for adjacency list and degree arrays.

"""

import sys

MOD = 10**9 + 7
MAXN = 2 * 10**5 + 5
fact = [1] * MAXN
for i in range(1, MAXN):
    fact[i] = (fact[i - 1] * i) % MOD


def solve():
    it = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(it)
    out_lines = []
    for _ in range(t):
        n = next(it)
        m = next(it)
        adj = [[] for _ in range(n)]
        deg = [0] * n
        for _ in range(m):
            u = next(it) - 1
            v = next(it) - 1
            adj[u].append(v)
            adj[v].append(u)
            deg[u] += 1
            deg[v] += 1
        # Check if graph is a tree (necessary condition for valid arrangement)
        if m != n - 1:
            out_lines.append("0")
            continue
        ans = 2  # Two possible sides for first node
        leaves = sum(1 for d in deg if d == 1)  # Count leaf nodes (degree 1)
        ok = True
        # Process each non-leaf node
        for u in range(n):
            if deg[u] > 1:
                x = 0
                # Count neighbors of degree 1 (leaves)
                for v in adj[u]:
                    if deg[v] == 1:
                        x += 1
                # If number of leaf neighbors is less than (degree - 2), invalid arrangement
                if x < deg[u] - 2:
                    ok = False
                    break
                # Multiply answer by factorial of leaf neighbors (permutations)
                ans = (ans * fact[x]) % MOD
        if not ok:
            out_lines.append("0")
            continue
        # If there are fewer leaves than n-1, then we can permute more
        if leaves < n - 1:
            ans = (ans * 2) % MOD
        out_lines.append(str(ans))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/