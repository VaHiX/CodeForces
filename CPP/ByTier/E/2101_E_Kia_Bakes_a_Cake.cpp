// Problem: CF 2101 E - Kia Bakes a Cake
// https://codeforces.com/contest/2101/problem/E

/*
Purpose: 
This code solves the problem of finding the maximum number of vertices in a "nice" simple path 
starting from each vertex labeled with '1' in a binary string, where the path must satisfy 
the condition that each edge weight is at least twice the previous edge weight. The vertices 
with '1' in the string are used to construct a complete weighted graph from a given tree.

Algorithms/Techniques:
- Tree decomposition using centroid decomposition
- Dynamic programming on trees
- BFS/DFS traversal for distance calculation
- Two-pointer technique with preprocessing and updates for efficient computation of maximum path lengths

Time Complexity: O(n log n) per test case, where n is the number of vertices in the tree.
Space Complexity: O(n) for storing graph structures and auxiliary arrays.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define drep(i, a, b) for (int i = a, i##end = b; i >= i##end; --i)
template <class T> inline void cmax(T &a, T b) { ((a < b) && (a = b)); }
template <class T> inline void cmin(T &a, T b) { ((a > b) && (a = b)); }
typedef pair<int, int> Pii;
const int N = 5e5 + 10;
int n, m;
string s;
int a[N];
vector<int> E[N];
vector<Pii> G[N];
int dp[N], ans[N];
void remove(vector<int> &G, int x) {
  rep(i, 0, G.size() - 1) if (G[i] == x) {
    G[i] = G.back();
    G.pop_back();
    break;
  }
}
void remove(vector<Pii> &G, int x) {
  rep(i, 0, G.size() - 1) if (G[i].first == x) {
    G[i] = G.back();
    G.pop_back();
    break;
  }
}
void dfs3(int u, int f) {
  remove(E[u], f);
  auto tmp = E[u];
  while (E[u].size() > 2) {
    int a = E[u].back();
    E[u].pop_back();
    int b = E[u].back();
    E[u].pop_back();
    E[u].pb(++m);
    G[m].pb(mp(a, a <= n)), G[m].pb(mp(b, 1));
    G[a].pb(mp(m, a <= n)), G[b].pb(mp(m, 1));
  }
  for (int v : E[u]) {
    G[u].pb(mp(v, v <= n)), G[v].pb(mp(u, v <= n));
  }
  for (int v : tmp)
    dfs3(v, u);
}
int mi, rta, rtb, rtw, siz[N], res[N], c[N];
void dfs(int u, int f, int n, int w) {
  siz[u] = 1, c[u] = u <= ::n && s[u] == '1';
  for (auto [v, w] : G[u])
    if (v != f) {
      dfs(v, u, n, w);
      siz[u] += siz[v];
      c[u] += c[v];
    }
  int ma = max(siz[u], n - siz[u]);
  if (mi > ma)
    mi = ma, rta = u, rtb = f, rtw = w;
}
int dis[N];
void dfs2(int u, int f, vector<Pii> &t) {
  if (u <= n && s[u] == '1')
    t.pb(mp(u, dis[u]));
  for (auto [v, w] : G[u])
    if (v != f) {
      dis[v] = dis[u] + w;
      dfs2(v, u, t);
    }
}
int W[N], C, s1[N], s2[N];
vector<Pii> lis1[N], lis2[N];
void update(int w, vector<Pii> &A, vector<Pii> &B) {
  int maxd1 = 0, maxd2 = 0;
  for (auto [_, d] : A)
    cmax(maxd1, d);
  for (auto [_, d] : B)
    cmax(maxd2, d);
  rep(i, 0, maxd1) s1[i] = -1e9;
  rep(i, 0, maxd2) s2[i] = -1e9;
  for (auto [u, d] : A) {
    int v = dp[u] / 2;
    if (d + w > v)
      continue;
    cmax(s2[min(maxd2, v - d - w)], d);
  }
  for (auto [u, d] : B) {
    int v = dp[u] / 2;
    if (d + w > v)
      continue;
    cmax(s1[min(maxd1, v - d - w)], d);
  }
  drep(i, maxd1, 1) cmax(s1[i - 1], s1[i]);
  drep(i, maxd2, 1) cmax(s2[i - 1], s2[i]);
  for (auto [u, d] : A)
    cmax(res[u], s1[d] + d + w);
  for (auto [u, d] : B)
    cmax(res[u], s2[d] + d + w);
}
void solve(int n, int u) {
  if (n == 1)
    return;
  mi = 1e9;
  dfs(u, 0, n, 0);
  int a = rta, b = rtb, w = rtw;
  remove(G[a], b), remove(G[b], a);
  if (c[a] && c[u] - c[a]) {
    lis1[++C].clear(), lis2[C].clear(), W[C] = w;
    dis[a] = dis[b] = 0;
    dfs2(a, 0, lis1[C]);
    dfs2(b, 0, lis2[C]);
  }
  if (c[u] - c[a] > 1)
    solve(n - siz[a], b);
  if (c[a] > 1)
    solve(siz[a], a);
  G[a].pb(mp(b, w));
  G[b].pb(mp(a, w));
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    m = n;
    cin >> s;
    s = ' ' + s;
    rep(i, 2, n) {
      int u, v;
      cin >> u >> v;
      E[u].pb(v), E[v].pb(u);
    }
    dfs3(1, 0);
    rep(i, 1, n) if (s[i] == '1') dp[i] = n * 2;
    else dp[i] = 0, ans[i] = -1;
    C = 0, solve(m, 1);
    rep(d, 1, 18) {
      int f = 0;
      rep(i, 1, n) if (dp[i] > 0) ans[i] = d, f = 1;
      if (!f)
        break;
      rep(i, 1, C) update(W[i], lis1[i], lis2[i]);
      rep(i, 1, n) dp[i] = res[i], res[i] = 0;
    }
    rep(i, 1, n) printf("%d ", ans[i]);
    puts("");
    rep(i, 1, m) G[i].clear(), E[i].clear();
  }
}


// https://github.com/VaHiX/CodeForces/