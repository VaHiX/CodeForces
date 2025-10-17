/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/E1
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 405, M = N * N, INF = 0x3f3f3f3f;
int T;
int n, m, q, f[N][N][N];

struct Edge {
  int u, v, w;
} e[M];
bool cmpByW(const Edge &a, const Edge &b) { return a.w < b.w; }

int fa[N];
int find_set(int v) { return fa[v] == v ? v : fa[v] = find_set(fa[v]); }

int W[N];
void solve() {
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      f[0][i][j] = INF;
  for (int i = 1; i <= m; ++i) {
    cin >> e[i].u >> e[i].v >> e[i].w;
    f[0][e[i].u][e[i].v] = f[0][e[i].v][e[i].u] = 1;
  }
  sort(e + 1, e + m + 1, cmpByW);
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        f[0][i][j] = min(f[0][i][j], f[0][i][k] + f[0][k][j]);

  for (int i = 1; i <= n; ++i)
    f[0][i][i] = 0;
  int mcnt = 0;
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int t = 1, u, v; t <= m; ++t) {
    u = find_set(e[t].u), v = find_set(e[t].v);
    if (u == v)
      continue;
    fa[v] = u;
    W[++mcnt] = e[t].w;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        f[mcnt][i][j] =
            min({f[mcnt - 1][i][j], f[mcnt - 1][i][u] + f[mcnt - 1][v][j],
                 f[mcnt - 1][i][v] + f[mcnt - 1][u][j]});
  }

  while (q--) {
    int a, b, K;
    cin >> a >> b >> K;
    int l = 1, r = mcnt;
    while (l < r) {
      int mid = l + r >> 1;
      if (f[mid][a][b] <= K - 1)
        r = mid;
      else
        l = mid + 1;
    }
    cout << W[l] << ' ';
  }
  cout << '\n';
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  cin >> T;
  while (T--)
    solve();
  return 0;
}