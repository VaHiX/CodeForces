/*
 * Problem URL : https://codeforces.com/problemset/problem/2110/D
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> Map[200005];
int n, val[200005], dp[200005];
int topology(int k) {
  for (int i = 1; i <= n; i++)
    dp[i] = 0;
  for (int u = 1; u < n; u++) {
    if (u != 1 && !dp[u])
      continue;
    dp[u] = min(k, dp[u] + val[u]);
    for (auto [v, w] : Map[u]) {
      if (dp[u] >= w)
        dp[v] = max(dp[v], dp[u]);
    }
  }
  return dp[n];
}
int main() {
  int T, m, a, b, w;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
      scanf("%d", val + i);
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d", &a, &b, &w);
      Map[a].push_back({b, w});
    }
    int l = 1, r = 1e9, mid;
    while (l <= r) {
      mid = (l + r) / 2;
      if (topology(mid))
        r = mid - 1;
      else
        l = mid + 1;
    }
    printf("%d\n", l == 1e9 + 1 ? -1 : l);
    for (int i = 1; i <= n; i++)
      Map[i].clear();
  }
  return 0;
}