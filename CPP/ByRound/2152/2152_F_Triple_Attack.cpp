// Problem: CF 2152 F - Triple Attack
// https://codeforces.com/contest/2152/problem/F

/*
F. Triple Attack
Algorithms/Techniques: 
  - Binary Lifting for LCA computation
  - Two-pointer technique for building tree structure
  - Segment tree / Binary lifting for range queries

Time Complexity: O(n log n + q log n) per test case
Space Complexity: O(n log n)

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define Mz 998244353
int x[250005];
int d[250005], dd[250005], f[250005][25], ff[250005][25];
vector<int> son[250005], vec[250005], dis[250005];

// Binary lifting to compute the LCA of two nodes
void dfs(int x) {
  for (int i = 1; i <= 20; i++)
    f[x][i] = f[f[x][i - 1]][i - 1];
  for (int i = 0; i < son[x].size(); i++) {
    int u = son[x][i];
    d[u] = d[x] + 1;
    f[u][0] = x;
    dfs(u);
  }
}

// LCA computation using binary lifting
int lca(int u, int v) {
  for (int i = 20; i >= 0; i--) {
    if (d[f[u][i]] >= d[v])
      u = f[u][i];
    if (d[f[v][i]] >= d[u])
      v = f[v][i];
  }
  for (int i = 20; i >= 0; i--) {
    if (f[u][i] != f[v][i]) {
      u = f[u][i];
      v = f[v][i];
    }
  }
  if (u != v)
    u = f[u][0];
  return u;
}

// Second DFS to build a secondary tree for distance tracking
void dfss(int x) {
  for (int i = 1; i <= 20; i++)
    ff[x][i] = ff[ff[x][i - 1]][i - 1];
  for (int i = 0; i < vec[x].size(); i++) {
    int u = vec[x][i], len = dis[x][i];
    dd[u] = dd[x] + len;
    ff[u][0] = x;
    dfss(u);
  }
}

// Query node depths using binary lifting
int qry(int x, int y) {
  int u = x;
  for (int i = 20; i >= 0; i--) {
    if (f[u][i] >= y)
      u = f[u][i];
  }
  return d[x] - d[f[u][0]];
}

// Range query using binary lifting and distance tracking
int ask(int l, int r) {
  int now = 0;
  for (int i = 20; i >= 0; i--) {
    if (ff[r][i] >= l) {
      now += dd[r] - dd[ff[r][i]];
      r = ff[r][i];
    }
  }
  now += qry(r, l);
  if (r - 1 >= l)
    now += qry(r - 1, l);
  return now;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  int t, n, z, l, r, q;
  cin >> t;
  while (t--) {
    cin >> n >> z;
    son[0].clear();
    vec[0].clear();
    dis[0].clear();
    for (int i = 1; i <= n; i++) {
      cin >> x[i];
      son[i].clear();
      vec[i].clear();
      dis[i].clear();
    }
    l = 0;
    // Build tree using two pointers: for each node, connect all nodes in range [l+1, i] with distance < z
    for (int i = 1; i <= n; i++) {
      while (x[l + 1] < x[i] - z)
        l++;
      son[l].push_back(i);
    }
    dfs(0); // Build the LCA tree
    for (int i = 1; i <= n; i++) {
      if (f[i][0] < i - 1) {
        // Add edge to parent with computed distance
        l = lca(i - 1, i);
        vec[l].push_back(i);
        dis[l].push_back(d[i] + d[i - 1] - 2 * d[l]);
      } else {
        // Add direct parent edge (distance is 1)
        vec[i - 1].push_back(i);
        dis[i - 1].push_back(1);
      }
    }
    dfss(0); // Build distance tracking tree
    cin >> q;
    while (q--) {
      cin >> l >> r;
      cout << ask(l, r) << "\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/