// Problem: CF 1778 E - The Tree Has Fallen!
// https://codeforces.com/contest/1778/problem/E

/*
 * Problem: E. The Tree Has Fallen!
 * Purpose: Find the maximum XOR value achievable by selecting nodes from the subtree of a given node,
 *          when the tree is rooted at another given node.
 *
 * Algorithms/Techniques:
 * - Heavy-Light Decomposition (HLD) for efficient subtree queries
 * - Linear basis (XOR basis) for maximum XOR computation
 * - LCA (Lowest Common Ancestor) computation using HLD
 *
 * Time Complexity: O(n * 32 + q * 32)
 * Space Complexity: O(n * 32)
 */

#include <stddef.h>
#include <iostream>
#include <utility>

#define endl '\n'
using namespace std;
const int N = 2e5 + 5, M = N << 1;
int e[M], ne[M], h[N], idx;
int son[N], fa[N], siz[N], dep[N];
int dfn[N], rdf[N], top[N], tim;
int a[N], d[32], T[N][32], pos[N][32];
int n, m, now;

// Add edge to adjacency list
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

// First DFS: compute subtree sizes, depths, and heavy son
void dfs0(int p, int f) {
  siz[p] = 1;
  dep[p] = dep[f] + 1;
  fa[p] = f;
  int maxv = -1;
  for (int i = h[p]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == f)
      continue;
    dfs0(j, p);
    siz[p] += siz[j];
    if (siz[j] > maxv) {
      maxv = siz[j];
      son[p] = j;
    }
  }
}

// Second DFS: perform heavy-light decomposition
void dfs1(int p, int t) {
  dfn[p] = ++tim;
  rdf[tim] = p;
  top[p] = t;
  if (son[p])
    dfs1(son[p], t);
  for (int i = h[p]; ~i; i = ne[i]) {
    int j = e[i];
    if (!dfn[j])
      dfs1(j, j);
  }
}

// Insert value into linear basis (XOR basis)
void insert(int x, int p) {
  for (int i = 0; i < 32; i++) {
    T[p][i] = T[p - 1][i];
    pos[p][i] = pos[p - 1][i];
  }
  int q = p;
  for (int i = 31; i >= 0; i--) {
    if (x >> i & 1) {
      if (T[p][i]) {
        if (pos[p][i] < q) {
          swap(pos[p][i], q);
          swap(T[p][i], x);
        }
        x ^= T[p][i];
      } else {
        T[p][i] = x;
        pos[p][i] = q;
        break;
      }
    }
  }
}

// Find Lowest Common Ancestor (LCA) using HLD
int LCA(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]])
      swap(x, y);
    now = top[x];
    x = fa[top[x]];
  }
  if (dep[x] != dep[y]) {
    if (dep[x] < dep[y])
      now = rdf[dfn[x] + 1];
    else
      now = rdf[dfn[y] + 1];
  }
  return dep[x] < dep[y] ? x : y;
}

// Query maximum XOR in a range using linear basis
int query(int l, int r) {
  int res = 0;
  for (int i = 31; i >= 0; i--) {
    if (pos[r][i] < l)
      continue;
    if ((res ^ T[r][i]) > res)
      res ^= T[r][i];
  }
  return res;
}

// Solve for current test case
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    for (int j = 0; j < 32; j++)
      T[i][j] = pos[i][j] = 0;
    son[i] = dfn[i] = 0;
    h[i] = -1;
  }
  idx = tim = 0;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    add(a, b);
    add(b, a);
  }
  dfs0(1, 0);
  dfs1(1, 1);
  for (int i = 1; i <= n; i++)
    insert(a[rdf[i]], i);
  cin >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    if (a == b) {
      int res = 0;
      for (int i = 31; i >= 0; i--)
        if ((res ^ T[n][i]) > res)
          res ^= T[n][i];
      cout << res << endl;
      continue;
    }
    int lca = LCA(a, b);
    if (lca != b) {
      cout << query(dfn[b], dfn[b] + siz[b] - 1) << endl;
    } else {
      int l = dfn[now] - 1, r = dfn[now] + siz[now];
      for (int i = 0; i < 32; i++)
        d[i] = T[l][i];
      for (int i = 31; i >= 0; i--) {
        if (pos[n][i] < r || !T[n][i])
          continue;
        else {
          int x = T[n][i];
          for (int j = 31; j >= 0; j--) {
            if (!(x >> j & 1))
              continue;
            if (d[j])
              x ^= d[j];
            else {
              d[j] = x;
              break;
            }
          }
        }
      }
      int res = 0;
      for (int i = 31; i >= 0; i--)
        if ((res ^ d[i]) > res)
          res ^= d[i];
      cout << res << endl;
    }
  }
}

// Main function to handle multiple test cases
signed main(void) {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/