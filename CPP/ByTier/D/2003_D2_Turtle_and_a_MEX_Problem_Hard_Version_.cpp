/*
 * Problem URL : https://codeforces.com/contest/2003/problem/D2
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

bool vis[N];
vector<int> g[N];
int T, n, m, dp[N];

void Solve() {
  cin >> n >> m;
  int V = 0;
  long long ans = 1ll * m * (m + 1) / 2;
  for (int i = 1, l; i <= n; i++) {
    cin >> l;
    for (int j = 0; j <= l + 1; j++)
      vis[j] = 0;
    for (int j = 1, x; j <= l; j++) {
      cin >> x;
      if (x <= l + 1)
        vis[x] = 1;
    }
    int u = 0;
    for (int j = 0; j <= l; j++) {
      u = j;
      if (!vis[j])
        break;
    }
    vis[u] = 1;
    int v = 0;
    for (int j = 0; j <= l + 1; j++) {
      v = j;
      if (!vis[j])
        break;
    }
    g[u].push_back(v);
    V = max(V, l + 1);
  }
  for (int i = 0; i <= V; i++) {
    dp[i] = i;
  }
  int maxx = 0;
  for (int i = V; i >= 0; i--) {
    for (int v : g[i]) {
      dp[i] = max(dp[i], dp[v]);
    }
    if (g[i].size() > 1)
      maxx = max(maxx, dp[i]);
    if (g[i].size())
      maxx = max(maxx, i);
    g[i].clear();
  }
  for (int i = 0; i <= min(V, m); i++) {
    ans += max(maxx, dp[i]) - i;
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--; Solve()) {
  }
  return 0;
}
/*
1
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
*/
