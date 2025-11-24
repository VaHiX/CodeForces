// Problem: CF 1702 G2 - Passable Paths (hard version)
// https://codeforces.com/contest/1702/problem/G2

/*
Algorithm: 
- This solution uses Lowest Common Ancestor (LCA) technique with binary lifting to determine if a set of vertices in a tree forms a passable path.
- A set of vertices is passable if there exists a simple path in the tree that visits all vertices of the set without reusing any edge.
- The key insight is that a set of vertices is passable exactly when:
  1. The LCA of all pairs of consecutive vertices in the sorted order (by DFS time) is one of the vertices in the set.
  2. No more than one "gap" occurs, where the LCA of two consecutive vertices is not one of the vertices in the set.
  3. If there is a gap, it must be consistent (i.e., it doesn't disconnect the path).

Time Complexity: O(n log n + q * k log k) where n is the number of nodes, q is the number of queries, and k is the maximum size of a query set.
Space Complexity: O(n log n) for the LCA preprocessing, plus O(k) for each query.

*/
#include <stdio.h>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;
const int N = 2e5 + 7;
basic_string<int> e[N]; // adjacency list for the tree
int n, m, i, j, x, y, k, ind, dfn[N], f[N][21], d[N], a[N]; // dfn: DFS time, f: binary lifting table, d: depth

// DFS to compute DFS time, depth and ancestors
void dfs(int x, int fa) {
  dfn[x] = ++ind; // assign DFS time
  f[x][0] = fa;   // set first ancestor
  d[x] = d[fa] + 1; // set depth
  for (auto &y : e[x]) // traverse neighbors
    if (y != fa)
      dfs(y, x); // recursive call
}

// LCA using binary lifting
int lca(int x, int y) {
  if (d[x] < d[y])
    swap(x, y); // make x deeper than y
  int t = d[x] - d[y];
  for (int i = 20; i >= 0; --i) // move x up to same level as y
    if (t >> i & 1)
      x = f[x][i];
  for (int i = 20; i >= 0; --i) // move both up until LCA
    if (f[x][i] != f[y][i])
      x = f[x][i], y = f[y][i];
  return x == y ? x : f[x][0]; // return LCA
}

int main() {
  // Read tree edges
  for (scanf("%d", &n), i = 1; i < n; ++i)
    scanf("%d%d", &j, &k), e[j] += k, e[k] += j;
  
  // Build DFS tree and compute LCA preprocessing
  for (dfs(1, 0), i = 1; i <= 20; ++i) // binary lifting precompute
    for (int j = 1; j <= n; ++j)
      f[j][i] = f[f[j][i - 1]][i - 1];
  
  // Process queries
  for (scanf("%d", &m); m--;) {
    for (scanf("%d", &k), i = 1; i <= k; ++i)
      scanf("%d", a + i); // read vertex set
    
    // Sort vertices by DFS time
    for (sort(a + 1, a + k + 1, [&](int x, int y) { return dfn[x] < dfn[y]; }),
         x = 0, y = 0, i = 1;
         i < k; ++i) {
      // Check if LCA of consecutive vertices is a vertex in the set
      if (lca(a[i], a[i + 1]) != a[i]) {
        x++; // count gaps
        if (lca(a[i], a[i + 1]) != lca(a[1], a[k]))
          y++; // check consistency
      }
    }
    // Output result based on gap count and consistency
    puts(x <= 1 && y == 0 ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/CodeForces/