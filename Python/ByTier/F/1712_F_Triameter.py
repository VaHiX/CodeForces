# Problem: CF 1712 F - Triameter
# https://codeforces.com/contest/1712/problem/F

"""
Algorithm: Tree Diameter Calculation with Dynamic Updates
Approach:
- Build the tree from parent information and compute depths.
- Identify leaf nodes (degree 1).
- Use BFS to compute distances from leaves to all nodes.
- For each query:
  - Add edges between all pairs of leaves with weight x_i.
  - Use dynamic programming on tree to compute updated diameters.

Time Complexity: O(n * q * log n) in worst case due to nested loops over tree nodes and queries.
Space Complexity: O(n * q) for storing the val array and other data structures.

This code computes the diameter of a tree after adding edges between all leaf nodes with a given weight.
"""
import sys
from collections import deque


def solve_problem():
    data = sys.stdin.read().strip().split()
    idx = 0

    n = int(data[idx])
    idx += 1

    f = [0] * n
    d = [0] * n

    g = [[] for _ in range(n)]
    g2 = [[] for _ in range(n)]

    # Build tree from parent information
    for i in range(1, n):
        p = int(data[idx])
        idx += 1
        p -= 1
        d[i] = d[p] + 1
        g[p].append(i)
        g2[i].append(p)

    used = [False] * n
    qe = deque()
    # Find all leaf nodes (degree == 1)
    for i in range(n):
        if len(g2[i]) + len(g[i]) == 1:
            qe.append(i)
            used[i] = True

    # BFS to calculate distance from leaves
    while qe:
        v = qe.popleft()
        for u in g[v]:
            if not used[u]:
                f[u] = f[v] + 1
                qe.append(u)
                used[u] = True
        for u in g2[v]:
            if not used[u]:
                f[u] = f[v] + 1
                qe.append(u)
                used[u] = True

    q = int(data[idx])
    idx += 1
    x = [0] * q
    ans = [0] * q
    # Read queries
    for i in range(q):
        x[i] = int(data[idx])
        idx += 1

    val = [[] for _ in range(n)]

    # Process nodes in reverse order (post-order traversal)
    for v in range(n - 1, -1, -1):
        for u in g[v]:
            # Swap if needed to keep smaller array first
            if len(val[u]) > len(val[v]):
                val[u], val[v] = val[v], val[u]

            # Update answer based on combinations of paths
            for fu in range(len(val[u])):
                for qi in range(q):
                    while True:
                        fv = max(0, ans[qi] - fu - x[qi])
                        if (
                            fv < len(val[v])
                            and val[v][fv] + val[u][fu] - 2 * d[v] >= ans[qi]
                        ):
                            ans[qi] += 1
                        else:
                            break

            # Merge values from child to parent
            for fu in range(len(val[u])):
                val[v][fu] = max(val[v][fu], val[u][fu])

            val[u].clear()

        fu = f[v]
        # Check direct combinations with current node
        for qi in range(q):
            while True:
                fv = max(0, ans[qi] - fu - x[qi])
                if fv < len(val[v]) and val[v][fv] - d[v] >= ans[qi]:
                    ans[qi] += 1
                else:
                    break

        # Add new entry for current node
        if fu == len(val[v]):
            val[v].append(d[v])

    # Adjust final answers
    for i in range(q):
        ans[i] -= 1

    print(" ".join(map(str, ans)))


if __name__ == "__main__":
    solve_problem()


# https://github.com/VaHiX/CodeForces/