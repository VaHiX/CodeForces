/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;
int T, n, u, v, d[maxn], ans;
vector<int> e[maxn];
int dfs(int u, int fa) {
  int mx = d[u];
  ans = max(ans, mx);
  for (int &v : e[u])
    if (v != fa) {
      int x = dfs(v, u);
      ans = max(ans, mx + x - 2);
      mx = max(mx, d[u] + x - 2);
    }
  e[u].clear();
  return mx;
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    ans = 0;
    for (int i = 1; i < n; i++) {
      scanf("%d%d", &u, &v);
      e[u].emplace_back(v);
      e[v].emplace_back(u);
      d[u]++;
      d[v]++;
    }
    dfs(1, 0);
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
      d[i] = 0;
  }
  return 0;
}