// Problem: CF 2106 G2 - Baudelaire (hard version)
// https://codeforces.com/contest/2106/problem/G2

/*
G2. Baudelaire (hard version)
Algorithms/Techniques: Tree decomposition using centroid decomposition, interactive queries, binary search on answers.

Time Complexity: O(n log^2(n)) per test case due to centroid decomposition and binary search
Space Complexity: O(n) for storing the tree structure and auxiliary arrays

This problem involves finding the values of nodes in an unrooted tree by asking two types of queries:
1. Sum of path values from root to specified nodes.
2. Toggle value of a specific node.

The solution uses centroid decomposition to efficiently find the root, then performs binary search on the query results
to determine node values.
*/
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int T, n, vis[1005];
vector<int> G[1005];
namespace Gravity_Point {
int nn, rt, mxs;
// Calculate size of subtree rooted at u, avoiding parent fa and visited nodes
int getsize(int u, int fa) {
  int sz = 1;
  for (int v : G[u]) {
    if (v == fa || vis[v])
      continue;
    sz += getsize(v, u);
  }
  return sz;
}
// Find centroid of subtree rooted at u
int dfs(int u, int fa) {
  int sz = 1, mx = 0;
  for (int v : G[u]) {
    if (v == fa || vis[v])
      continue;
    int siz = dfs(v, u);
    mx = max(mx, siz);
    sz += siz;
  }
  mx = max(mx, nn - sz);
  if (mx < mxs)
    mxs = mx, rt = u;
  return sz;
}
// Return centroid of tree rooted at u
int findrt(int u) {
  nn = getsize(u, 0);
  rt = 0, mxs = 1e9;
  dfs(u, 0);
  return rt;
}
}; // namespace Gravity_Point
using Gravity_Point::findrt;
vector<int> P[1005];
int m;
// Add all nodes in subtree of u (excluding fa) to P[m]
void add(int u, int fa) {
  P[m].emplace_back(u);
  for (int v : G[u]) {
    if (v == fa || vis[v])
      continue;
    add(v, u);
  }
}
// Check if node u is in the same component as the answer based on queries
bool check(int l, int r, int u) {
  vector<int> node;
  for (int i = l; i <= r; i++)
    for (int v : P[i])
      node.emplace_back(v);
  cout << "? 1 " << node.size() << " ";
  for (int v : node)
    cout << v << " ";
  cout << endl;
  int r1;
  cin >> r1;
  cout << "? 2 " << u << endl;
  cout << "? 1 " << node.size() << " ";
  for (int v : node)
    cout << v << " ";
  cout << endl;
  int r2;
  cin >> r2;
  if (abs(r1 - r2) / 2 == node.size())
    return false;
  return true;
}
// Binary search to find component where the answer belongs
int search(int l, int r, int u) {
  if (l == r)
    return l;
  int mid = (l + r) >> 1;
  if (check(l, mid, u))
    return search(l, mid, u);
  else
    return search(mid + 1, r, u);
}
// DFS to find root using centroid decomposition and solve for node values
int dfs(int u) {
  vis[u] = 1, m = 0;
  for (int v : G[u]) {
    if (vis[v])
      continue;
    ++m;
    P[m].clear();
    add(v, u);
  }
  if (m == 0)
    return u;
  if (!check(1, m, u))
    return u;
  int cho = search(1, m, u);
  int v = P[cho][0];
  return dfs(findrt(v));
}
// DFS to compute final node values
int res[10005];
void dfs1(int u, int fa, int pre) {
  cout << "? 1 1 " << u << endl;
  cin >> res[u];
  res[u] -= pre;
  for (int v : G[u]) {
    if (v == fa)
      continue;
    dfs1(v, u, pre + res[u]);
  }
}
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    G[i].clear(), vis[i] = 0;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  int rt = dfs(findrt(1));
  dfs1(rt, 0, 0);
  cout << "! ";
  for (int i = 1; i <= n; i++)
    cout << res[i] << " ";
  cout << endl;
}
int main() {
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/