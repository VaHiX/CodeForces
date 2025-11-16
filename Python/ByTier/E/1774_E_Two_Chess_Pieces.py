# Problem: CF 1774 E - Two Chess Pieces
# https://codeforces.com/contest/1774/problem/E

"""
Algorithm: Tree Traversal and Dynamic Programming on Trees
Approach:
1. Build a tree from input edges.
2. For each node, track:
   - Whether it's part of the path for piece 1 or 2 (seq1, seq2)
   - Maximum distance from root for piece 1 or 2 (dist1, dist2)
3. Perform DFS to calculate minimum steps needed to ensure that both pieces never exceed distance d from each other.

Time Complexity: O(n)
Space Complexity: O(n)
"""

import sys
from array import array
from collections import deque

input = lambda: sys.stdin.readline().rstrip("\r\n")
inp = lambda dtype: [dtype(x) for x in input().split()]
debug = lambda *x: print(*x, file=sys.stderr)
ceil1 = lambda a, b: (a + b - 1) // b
Mint, Mlong = 2**31 - 1, 2**63 - 1
out, tests = [], 1


class graph:
    def __init__(self, n):
        self.n = n
        # Initialize adjacency list
        self.gdict = [array("i") for _ in range(n + 1)]

    def add_edge(self, node1, node2):
        # Add bidirectional edges
        self.gdict[node1].append(node2)
        self.gdict[node2].append(node1)

    def subtree(self, root):
        # BFS to get parent info and child nodes 
        queue, visit = deque([root]), array("b", [0] * (self.n + 1))
        child = array("i")
        # Initialize parent array
        self.par, visit[root] = array("i", [-1] * (self.n + 1)), True

        while queue:
            s = queue.popleft()

            for i1 in self.gdict[s]:
                if not visit[i1]:
                    queue.append(i1)
                    visit[i1] = True
                    child.append(i1)
                    self.par[i1] = s

        # Traverse nodes from leaves to root to compute distances
        for ch in child[::-1]:
            # Update maximum distances for piece 1 and 2
            dist1[self.par[ch]] = max(dist1[self.par[ch]], dist1[ch] + seq2[ch])
            dist2[self.par[ch]] = max(dist2[self.par[ch]], dist2[ch] + seq1[ch])
            # Update presence of required nodes
            seq1[self.par[ch]] |= seq1[ch]
            seq2[self.par[ch]] |= seq2[ch]

    def dfs(self, root):
        # DFS to count necessary moves
        stk, vis = array("i", [root]), array("b", [0] * (self.n + 1))
        vis[root], ret = 1, 0

        while stk:
            par = stk.pop()
            for ch in self.gdict[par]:
                if not vis[ch]:
                    vis[ch] = 1
                    stk.append(ch)

                    # If path is required or distance constraint violated for piece 1
                    if seq1[ch] or dist1[ch] + 1 > d:
                        ret += 2
                    # If path is required or distance constraint violated for piece 2
                    if seq2[ch] or dist2[ch] + 1 > d:
                        ret += 2

        return ret


for _ in range(tests):
    n, d = inp(int)
    g = graph(n)
    # Read edges and build graph
    for _ in range(n - 1):
        u, v = inp(int)
        g.add_edge(u, v)

    # Initialize arrays for tracking paths and distances
    seq1, seq2 = array("b", [0] * (n + 1)), array("b", [0] * (n + 1))
    dist1, dist2 = array("i", [0] * (n + 1)), array("i", [0] * (n + 1))
    
    # Mark required nodes for first piece
    for i in array("i", inp(int))[1:]:
        seq1[i] = 1
    # Mark required nodes for second piece
    for i in array("i", inp(int))[1:]:
        seq2[i] = 1

    # Compute subtree info
    g.subtree(1)
    # Compute minimum steps required
    out.append(g.dfs(1))

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/