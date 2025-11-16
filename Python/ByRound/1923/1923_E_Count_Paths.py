# Problem: CF 1923 E - Count Paths
# https://codeforces.com/contest/1923/problem/E

"""
Algorithm: Tree DFS Traversal
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks to count "beautiful" paths in a tree, where:
- A path is beautiful if:
  1. It has at least 2 vertices.
  2. The first and last vertices are the same color.
  3. No other vertex on the path has the same color as the first vertex.

Approach:
- Use DFS traversal of the tree.
- For each vertex, maintain:
  - `cntc[c[v]]`: Number of vertices with the same color in the current path from root to this vertex.
  - `up[c[v]]`: Number of valid paths ending at vertices of the same color that have been processed.
- During DFS:
  - For each neighbor, recursively process it.
  - Before processing, we count how many valid paths are already found before entering this subtree.
  - After processing child subtrees, update counts for current vertex to propagate upward.
- This ensures we correctly count all paths that satisfy the condition.

The recursion uses `up` and `cntc` arrays to track the number of vertices with the same color seen so far and to count valid paths that have been closed off.
"""

import sys

sys.setrecursionlimit(1 << 25)


def solve():
    t = int(input())
    for _ in range(t):
        n = int(input())
        c = [0] + list(map(int, input().split()))  # Color array (1-indexed)
        cntc = [0] * (n + 2)  # Counter for vertices of each color in current path
        up = [0] * (n + 2)    # Tracks number of "open" paths ending at a given color
        e = [[] for _ in range(n + 2)]  # Adjacency list
        ans = [0]  # Result counter (mutable list for inner function access)

        # Build adjacency list
        for _ in range(n - 1):
            u, v = map(int, input().split())
            e[u].append(v)
            e[v].append(u)

        def dfs(v, parent):
            # Count of same-colored vertices before entering this node's subtree
            u_count = cntc[c[v]]
            # Count of paths ending at same color before entering subtree
            s_count = up[c[v]]
            # Add valid paths that end at this node (from previous traversal)
            ans[0] += s_count
            
            # Traverse children
            for u in e[v]:
                if u == parent:
                    continue
                # Reset up count for current color (we're exploring new branch)
                up[c[v]] = 0
                dfs(u, v)  # Recursive DFS on child

            # At this point, all paths ending at nodes in the subtree have been counted via the recursive calls

            # Update counts for the current node's subtree for upward propagation
            ans[0] += cntc[c[v]] - u_count  # Add number of newly closed paths
            cntc[c[v]] = u_count + 1  # Increment count of this color encountered
            up[c[v]] = s_count + 1    # Propagate upward how many valid paths ended here

        dfs(1, 0)
        print(ans[0])


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/