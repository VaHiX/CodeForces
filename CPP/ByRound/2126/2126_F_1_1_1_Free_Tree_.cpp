/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/F
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5;
ll T, n, q, u, v, c, x, ans, a[N], fa[N], w[N];
vector<pair<ll, ll>> G[N];
map<ll, ll> mp[N];
void dfs(ll x) {
  for (pair<ll, ll> y : G[x]) {
    if (y.first != fa[x]) {
      fa[y.first] = x;
      w[y.first] = y.second;
      mp[x][a[y.first]] += y.second;
      dfs(y.first);
    }
  }
  ans -= mp[x][a[x]];
}
int main() {
  ios::sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> q;
    ans = 0;
    for (ll i = 1; i <= n; i++) {
      cin >> a[i];
      G[i].clear();
      mp[i].clear();
    }
    for (ll i = 1; i < n; i++) {
      cin >> u >> v >> c;
      ans += c;
      G[u].push_back({v, c});
      G[v].push_back({u, c});
    }
    dfs(1);
    for (ll i = 1; i <= q; i++) {
      cin >> v >> x;
      ans += mp[v][a[v]];
      ans -= mp[v][x];
      ans += mp[fa[v]][a[fa[v]]];
      mp[fa[v]][a[v]] -= w[v];
      mp[fa[v]][x] += w[v];
      ans -= mp[fa[v]][a[fa[v]]];
      a[v] = x;
      cout << ans << "\n";
    }
  }
  return 0;
}