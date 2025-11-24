// Problem: CF 2108 E - Spruce Dispute
// https://codeforces.com/contest/2108/problem/E

/*
E. Spruce Dispute
Algorithms/Techniques: Tree center finding, DFS traversal, edge removal optimization
Time Complexity: O(n) per test case
Space Complexity: O(n)

This problem involves selecting an edge to remove from a tree such that the sum of path lengths
between same-colored ornaments is maximized. The approach uses tree centroid decomposition:
- First, find the centroid (center) of the tree.
- Then evaluate all edges to choose the one whose removal maximizes the desired sum.
- Assign colors to vertices in a way that minimizes the number of vertices assigned to each color,
  which helps maximize path lengths.

The algorithm performs two DFS traversals:
1. To find the centroid (center node) and compute subtree sizes.
2. To compute depths from the centroid for optimal edge selection.

Finally, a reassignment of colors is done based on traversal order.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 2e5 + 5;
int T, n, head[N], ecnt;
struct Edge {
  int to, nxt;
} e[N << 1];
void addedge(int x, int y) {
  e[++ecnt] = {y, head[x]}; // Add edge from x to y
  head[x] = ecnt;
}
int U, V, rt, sz[N], dep[N];
void dfs(int x, int fa) {
  int mx = 0;
  sz[x] = 1; // Initialize size of subtree rooted at x
  for (int i = head[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa)
      continue;
    dfs(y, x); // Recursive DFS call on child y
    mx = max(sz[y], mx); // Track maximum subtree size
    sz[x] += sz[y]; // Accumulate subtree sizes
  }
  mx = max(mx, n - sz[x]); // Check the remaining part of tree
  if (mx <= n / 2) // If balanced around this node
    rt = x; // Mark it as centroid
}
void dfs1(int x, int fa) {
  sz[x] = 1;
  for (int i = head[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa)
      continue;
    dep[y] = dep[x] + 1; // Compute depth
    dfs1(y, x); // Recursive DFS call on child y
    sz[x] += sz[y]; // Accumulate subtree sizes
  }
}
int dfn[N], d;
void dfs2(int x, int fa) {
  if (x != V)
    dfn[x] = ++d; // Record depth-first number for node x, but skip node V
  if (d == n / 2)
    d = 0; // Reset counter when reaching half size
  for (int i = head[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa)
      continue;
    dfs2(y, x); // Recursive DFS call on child y
  }
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    ecnt = 0;
    for (int i = 1; i <= n; i++)
      dfn[i] = head[i] = 0;
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      addedge(x, y); // Build adjacency list
      addedge(y, x); // Bidirectional graph
    }
    dfs(1, 0); // Find centroid starting from node 1
    dep[rt] = 0; // Set depth of root to zero
    dfs1(rt, 0); // Traverse to calculate depths
    int delt = N << 1; // Initialize smallest delta value
    for (int u = 1; u <= n; u++) // Evaluate all edges
      for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, _delt;
        if (u > v)
          continue;
        if (dep[u] < dep[v])
          _delt = dep[v] + (sz[v] - 1); // Compute delta for this edge
        else if (dep[u] > dep[v])
          _delt = sz[u] + dep[v]; // Another case of delta value
        if (_delt < delt)
          U = u, V = v, delt = _delt; // Update best edge
      }
    if (V == rt)
      rt = U; // Adjust centroid if necessary
    d = 0;
    dfs2(rt, 0); // Perform final traversal to assign dfn values
    printf("%d %d\n", U, V);
    for (int i = 1; i <= n; i++)
      printf("%d ", dfn[i]); // Print color assignments
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/