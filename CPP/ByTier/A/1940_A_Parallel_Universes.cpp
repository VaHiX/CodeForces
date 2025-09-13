/*
 * Problem URL : https://codeforces.com/contest/1940/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
const int N = 3e5 + 5;
int n, m1, m2, fd[N];
unordered_map<int, int> G[N], H[N];
inline int find(const int &x) { return x == fd[x] ? x : fd[x] = find(fd[x]); }
inline void MAIN() {
  cin >> n >> m1 >> m2;
  for (int i = 1; i <= n; ++i)
    G[i].clear(), H[i].clear(), fd[i] = i;
  for (int i = 1; i <= m1; ++i) {
    int u, v;
    cin >> u >> v;
    H[u][v] = H[v][u] = 1, fd[find(u)] = find(v);
  }
  for (int i = 1; i <= m2; ++i) {
    int u, v;
    cin >> u >> v;
    G[u][v] = G[v][u] = 1;
  }
  bool ok = 1;
  for (int i = 1; i <= n; ++i)
    ok &= find(i) == find(1);
  if (ok)
    return cout << "Yes\n0\n", void();
  for (int u = 1; u <= n; ++u)
    for (int v = u + 1; v <= n; ++v)
      if (!(G[u][v] ^ H[u][v])) {
        vector<pair<int, int>> ans;
        if (!G[u][v])
          ans.emplace_back(u, v);
        for (int i = 1; i <= n; ++i)
          if (i != u && i != v && !H[u][i] && !H[v][i])
            ans.emplace_back(G[u][i] ? v : u, i);
        cout << "Yes\n" << ans.size() << '\n';
        for (auto [x, y] : ans)
          cout << x << ' ' << y << '\n';
        return;
      }
  if (n < 4)
    return cout << "No\n", void();
  vector<pair<int, int>> ans;
  int a = 1, b = 2, c = 3, d = 4;
  if (G[a][b] + G[b][c] + G[c][d] + H[c][a] + H[a][d] + H[d][b] > 3)
    a = 3, b = 1, c = 4, d = 2;
  if (H[c][a])
    ans.emplace_back(c, a);
  if (H[a][d])
    ans.emplace_back(a, d);
  if (H[d][b])
    ans.emplace_back(d, b);
  if (G[a][b])
    ans.emplace_back(a, b);
  if (G[b][c])
    ans.emplace_back(b, c);
  if (G[c][d])
    ans.emplace_back(c, d);
  for (int i = 1; i <= n; ++i)
    if (i != a && i != b && i != c && i != d)
      if (!H[i][a] && !H[i][b] && !H[i][c] && !H[i][d])
        ans.emplace_back(i, a);
  cout << "Yes\n" << ans.size() << '\n';
  for (auto [x, y] : ans)
    cout << x << ' ' << y << '\n';
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t, tid;
  cin >> t >> tid;
  while (t--)
    MAIN();
  return 0;
}