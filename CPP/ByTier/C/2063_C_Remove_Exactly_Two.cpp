/*
 * Problem URL : https://codeforces.com/problemset/problem/2063/C
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
int T, n, f[200005], ans;
vector<int> q[200005];
void dfs(int x, int fa) {
  int r = q[x].size();
  for (int i = 0; i < q[x].size(); i++) {
    int v = q[x][i];
    if (v == fa)
      continue;
    dfs(v, x);
    ans = max(ans, r + (int)q[v].size() - 2);
    ans = max(ans, r + f[v] - 1);
    ans = max(ans, f[x] + max(f[v], (int)q[v].size()) - 1);
    f[x] = max(f[x], max(f[v], (int)q[v].size()));
  }
}
void solve() {
  scanf("%d", &n);
  ans = 0;
  for (int i = 1; i <= n; i++)
    f[i] = 0, q[i].clear();
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    q[u].push_back(v);
    q[v].push_back(u);
  }
  dfs(1, 0);
  printf("%d\n", ans);
}
signed main() {
  scanf("%d", &T);
  while (T--)
    solve();
}