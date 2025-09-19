/*
 * Problem URL : https://codeforces.com/problemset/problem/1240/C
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
#define rint register int
#define deb(x) cerr << #x << " = " << (x) << '\n';
// #pragma GCC optimize(3,"Ofast","inline")
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
const int maxn = 5e5 + 5;
int q, n, k;
vector<pii> g[maxn];
ll dp[maxn][2];

void dfs(int u, int f) {
  ll tot = 0;
  vector<ll> v;
  for (auto it : g[u]) {
    int to = it.first;
    int w = it.second;
    if (to == f)
      continue;
    dfs(to, u);
    tot += dp[to][0];
    v.push_back(dp[to][1] + w - dp[to][0]);
  }
  sort(v.rbegin(), v.rend());
  for (int i = 0; i < min(int(v.size()), k); i++)
    if (v[i] > 0)
      tot += v[i];

  dp[u][0] = dp[u][1] = tot;
  if (int(v.size()) >= k)
    if (v[k - 1] > 0)
      dp[u][1] -= v[k - 1];
}

int main() {
  scanf("%d", &q);
  while (q--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
      g[i].clear();
    for (int i = 1; i < n; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      g[u].push_back(pii(v, w));
      g[v].push_back(pii(u, w));
    }
    dfs(1, 0);
    printf("%lld\n", dp[1][0]);
  }
}