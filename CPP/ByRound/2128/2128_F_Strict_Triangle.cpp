/*
 * Problem URL : https://codeforces.com/problemset/problem/2128/F
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define ll long long
#define sz(x) ((int)x.size())
using namespace std;
using pii = pair<ll, int>;
using tup = tuple<int, int, int>;
const int N = 200005;
int n, m, k, l[N], r[N];
vector<pii> G[N];
void solve() {
  scanf("%d%d%d", &n, &m, &k);
  rep(i, 1, n) G[i].clear();
  rep(i, 1, m) {
    int x, y;
    scanf("%d%d%d%d", &x, &y, &l[i], &r[i]);
    G[x].emplace_back(y, i), G[y].emplace_back(x, i);
  }
  vector<ll> dis(n + 1);
  vector<int> vs(n + 1);
  priority_queue<pii, vector<pii>, greater<pii>> q;
  rep(i, 1, n) dis[i] = 1e18;
  dis[k] = 0;
  q.emplace(0, k);
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vs[u])
      continue;
    vs[u] = 1;
    for (auto v : G[u])
      if (dis[v.first] > dis[u] + r[v.second]) {
        dis[v.first] = dis[u] + r[v.second];
        q.emplace(dis[v.first], v.first);
      }
  }
  rep(i, 1, n) vs[i] = 0;
  vector<ll> dp(n + 1);
  rep(i, 2, n) dp[i] = 1e18;
  dp[1] = -1e18;
  q.emplace(-1e18, 1);
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vs[u])
      continue;
    vs[u] = 1;
    if (dis[u] <= dp[u])
      continue;
    for (auto v : G[u])
      if (v.first != k) {
        ll nv = max(dp[u] + l[v.second], l[v.second] - dis[u]);
        if (nv < dp[v.first])
          dp[v.first] = nv, q.emplace(dp[v.first], v.first);
      }
  }
  if (dis[n] > dp[n])
    puts("YES");
  else
    puts("NO");
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
}