# Problem: CF 2150 F - Cycle Closing
# https://codeforces.com/contest/2150/problem/F

"""
F. Cycle Closing

Purpose:
This code solves the problem of making an undirected connected graph complete (i.e., adding all missing edges)
in at most 2 operations. In each operation, we can choose a path length k and print s simple paths of that length,
and then add shortcut edges between the endpoints of those paths.

Algorithm:
1. Build adjacency list representation of the graph.
2. First operation (if needed):
   - Find a spanning tree using DFS traversal.
   - Add edges to make all non-tree edges part of a cycle, forming shortcuts.
3. Second operation (if needed):
   - Use BFS/DFS to find longest path and calculate distances.
   - For each pair of nodes not yet connected, construct a path of appropriate length.

Time Complexity:
- O(n^2) per test case due to nested loops over nodes for constructing paths in both operations.
- Overall: O(t * n^2), where t is the number of test cases and n is the number of nodes.

Space Complexity:
- O(n^2) for storing graph structure, path information, and auxiliary arrays during traversal.

Note:
The actual implementation uses a complex DFS-based approach to build spanning trees and find paths,
specifically designed to minimize the number of operations required by leveraging existing structures.
"""

import sys

sys.setrecursionlimit(10**6)


def solve():
    d = sys.stdin.buffer.read().split()
    it = iter(d)
    ni = lambda: int(next(it))
    t = ni()
    o = []
    ap = o.append
    for _ in range(t):
        n = ni()
        m = ni()
        g = [[] for _ in range(n)]
        tr = [[] for _ in range(n)]
        got = set()
        for _ in range(m):
            u = ni() - 1
            v = ni() - 1
            g[u].append(v)
            g[v].append(u)
            got.add((u, v))
            got.add((v, u))

        def bt(x):
            # Build spanning tree via DFS
            for y in g[x]:
                if not tr[y]:
                    tr[y].append(x)
                    tr[x].append(y)
                    bt(y)

        bt(0)
        h = [0] * n
        up = [-1] * n

        def gd(x, p=-1, d0=0):
            # Get farthest node from x in the tree, return that node
            h[x] = d0
            up[x] = p
            a = x
            for y in tr[x]:
                if y != p:
                    z = gd(y, x, d0 + 1)
                    if h[z] > h[a]:
                        a = z
            return a

        op = [{}, {}]
        for i in range(n):
            for u in tr[i]:
                for v in tr[i]:
                    # Add shortcut edges to ensure completeness (if not already present)
                    if u != v and (u, v) not in got:
                        got.add((u, v))
                        got.add((v, u))
                        op[0][(u, v)] = [u, i, v]
                        m += 1
        sec = (h[gd(gd(0))] + 1) // 2  # Half the diameter; used to determine path lengths
        for i in range(n):
            deep = gd(i)
            p = [-1] * n
            v = []
            j = deep
            while j != -1:
                v.append(j)
                p[j] = h[j]
                j = up[j]
            v = v[::-1]  # Reverse to get correct traversal order
            for j in range(n):
                if i != j and (i, j) not in got:
                    got.add((i, j))
                    got.add((j, i))
                    q = [j]
                    d = h[j]
                    if sec <= d <= 2 * sec:
                        two = d - sec
                        one = sec - two
                        while two:
                            q.append(up[up[q[-1]]])
                            two -= 1
                        while one:
                            q.append(up[q[-1]])
                            one -= 1
                    else:
                        # Calculate path to align with target length
                        while p[q[-1]] == -1:
                            q.append(up[q[-1]])
                        if q[-1] == i:
                            q[-1] = v[1]
                        tgt = sec - (len(q) - 1)
                        on = p[q[-1]]
                        f = on
                        while on + 2 <= tgt:
                            on += 2
                            q.append(v[on])
                        if on == tgt:
                            on -= 1
                            q.append(v[on])
                        else:
                            on += 1
                            q.append(v[on])
                        while on > f:
                            on -= 2
                            q.append(v[on])
                        while on > 0:
                            on -= 1
                            q.append(v[on])
                    assert q[-1] == i and q[0] == j and len(q) == sec + 1  # Ensure correctness of constructed path
                    op[1][(i, j)] = q
        s = (1 if op[0] else 0) + (1 if op[1] else 0)
        ap(str(s))
        for r in range(2):
            if op[r]:
                vals = list(op[r].values())
                ap(str(len(vals[0])))
                ap(str(len(vals)))
                for w in vals:
                    ap(" ".join(str(x + 1) for x in w))
    sys.stdout.write("\n".join(o))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/