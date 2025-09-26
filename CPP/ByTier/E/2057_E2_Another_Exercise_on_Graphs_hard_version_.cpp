/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/E2
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 405;
struct dat {
  int u, v, w;
} e[N * N];
int dis[N][N][N], dst[N];
void ATRI() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      dis[0][i][j] = i == j ? 0 : 1e9;
  for (int i = 1, u, v, w; i <= m; ++i)
    cin >> u >> v >> w, e[i] = {u, v, w}, dis[0][u][v] = dis[0][v][u] = 1;
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[0][i][j] = min(dis[0][i][j], dis[0][i][k] + dis[0][k][j]);
  sort(e + 1, e + m + 1, [=](dat x, dat y) { return x.w < y.w; });
  int cnt = 0;
  for (int k = 1; k <= m; ++k) {
    auto [u, v, w] = e[k];
    if (!dis[cnt][u][v])
      continue;
    dst[++cnt] = w;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[cnt][i][j] = min(dis[cnt - 1][i][j],
                             min(dis[cnt - 1][i][u] + dis[cnt - 1][v][j],
                                 dis[cnt - 1][i][v] + dis[cnt - 1][u][j]));
  }
  while (q--) {
    int u, v, x;
    cin >> u >> v >> x;
    int l = 1, r = cnt, mid, res = -1;
    while (l <= r) {
      mid = l + r >> 1;
      if (dis[mid][u][v] < x)
        res = mid, r = mid - 1;
      else
        l = mid + 1;
    }
    cout << dst[res] << " \n"[!q];
  }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    ATRI();
  return 0;
}