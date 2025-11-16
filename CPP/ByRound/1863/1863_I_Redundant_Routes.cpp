// Problem: CF 1863 I - Redundant Routes
// https://codeforces.com/contest/1863/problem/I

/* 
 * Problem: Redundant Routes
 * 
 * Purpose:
 *   Given a tree with n vertices, select the maximum number of simple paths 
 *   (each of length at least 2) such that no two paths are contained one inside another.
 *   This is equivalent to finding the maximum number of edges in a "non-crossing" 
 *   edge set in a tree where each edge represents a path from one node to another, 
 *   and two paths are considered "contained" if one is a subpath of another.
 * 
 * Approach:
 *   1. Use a Union-Find (Disjoint Set Union) structure to group connected components.
 *   2. For each node, perform DFS to find neighbors and mark path relationships.
 *   3. Construct a graph where each edge represents a path in the original tree.
 *   4. Build a new tree from these paths such that paths that share a node are 
 *      connected in a hierarchical way.
 *   5. Perform DFS on this new structure to compute the maximum number of paths 
 *      that can be selected without one being a subpath of another.
 * 
 * Time Complexity:
 *   O(n^2 * α(n)) where α(n) is the inverse Ackermann function (nearly constant).
 *   The nested loops process each pair of nodes, and the Union-Find operations are nearly constant.
 * 
 * Space Complexity:
 *   O(n^2) for storing the adjacency lists and Union-Find structures.
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
const int maxn = 3005;
int n, rt, vis[maxn * maxn], hj[maxn * maxn][2];
vector<int> tree[maxn], ntr[maxn * maxn];
struct bcj {
  int fa[maxn * maxn], siz[maxn * maxn];
  void clear() {
    for (int i = 1; i <= n * n; ++i)
      fa[i] = i, siz[i] = 1;
  }
  int getf(int x) {
    if (fa[x] == x)
      return x;
    return fa[x] = getf(fa[x]);
  }
  void Merge(int x, int y) {
    x = getf(x);
    y = getf(y);
    if (x != y) {
      if (siz[x] > siz[y])
        swap(x, y);
      fa[x] = y;
      siz[y] += siz[x];
      siz[x] = 0;
    }
  }
} t1;
int gid(int x, int y) {
  if (x > y)
    swap(x, y);
  return (x - 1) * n + y;
}
void dfs(int root, int s, int fa) {
  // Record the two nodes connected to the current node root through path s
  if (s != root && fa != root) {
    int t1 = gid(root, s), t2 = gid(root, fa);
    if (hj[t1][0])
      hj[t1][1] = t2;
    else
      hj[t1][0] = t2;
  }
  // Continue DFS for all neighbors of s
  for (int j = 0; j < tree[s].size(); ++j) {
    int s_ = tree[s][j];
    if (s_ != fa)
      dfs(root, s_, s);
  }
}
int dfs_(int s) {
  vis[s] = 1;
  int res = 0;
  // Visit all children of s in the new tree and accumulate size
  for (int j = 0; j < ntr[s].size(); ++j) {
    int s_ = ntr[s][j];
    if (!vis[s_])
      res += dfs_(s_);
  }
  // Update the max size found so far
  res = max(res, t1.siz[s]);
  return res;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  // Read edges
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    rt = gid(u, v); // Mark the root for later use
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  t1.clear(); // Initialize Union-Find
  for (int i = 1; i <= n; ++i)
    dfs(i, i, 0); // Perform DFS from each node to identify relationships
  // Merge nodes in Union-Find based on path relationships
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) {
      int id = (i - 1) * n + j;
      if (hj[id][0])
        t1.Merge(hj[id][0], hj[id][1]);
    }
  // Construct the new tree representing the hierarchical structure of paths
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) {
      int id = (i - 1) * n + j;
      if (t1.fa[id] == id && hj[id][0])
        ntr[t1.getf(hj[id][0])].push_back(id);
    }
  rt = t1.getf(rt);
  cout << dfs_(rt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/