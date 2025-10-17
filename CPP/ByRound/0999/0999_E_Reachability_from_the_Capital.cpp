/*
 * Problem URL : https://codeforces.com/contest/999/problem/E
 * Submit Date : 2025-09-06
 */

// jiudge: 7747: 1649381667
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> G[5005];
int f[5005], cnt, a[5005], ans, n, m, s, u, v;
void dfs(int x) {
  for (int i = 0; i < G[x].size(); ++i) {
    if (!f[G[x][i]])
      f[G[x][i]] = 1, dfs(G[x][i]);
  }
}
signed main() {
  cin >> n >> m >> s;
  while (m--) {
    cin >> u >> v;
    G[u].push_back(v);
  }
  for (int i = 1; i <= n; ++i)
    if (!f[i])
      f[i] = 1, dfs(i), a[++cnt] = i;
  memset(f, 0, sizeof(f));
  f[s] = 1;
  dfs(s);
  for (int i = cnt; i; --i)
    if (!f[a[i]])
      f[a[i]] = 1, dfs(a[i]), ans++;
  cout << ans;
}