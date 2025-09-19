/*
 * Problem URL : https://codeforces.com/contest/2035/problem/F
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef long long ll;
const int N = 5e5 + 5;
int n, x;
ll a[N];
vector<int> adj[N];
ll dp[N];
ll boss;
void dfs(int id, int p) {
  ll need = a[id];
  for (auto c : adj[id]) {
    if (c == p)
      continue;
    dfs(c, id);
    need += dp[c];
  }
  ll hv = (boss + (n - id)) / n;
  ll mn = (need + hv) % 2;
  dp[id] = max(mn, need - hv);
}
bool check(ll t) {
  boss = t;
  dfs(x, 0);
  if (dp[x] == 0)
    return true;
  else
    return false;
}
void solve() {
  cin >> n >> x;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    adj[i].clear();
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  ll ans = ((ll)2e9 + 5) * (2 * n);
  ll funny = ans;
  int counter = 2 * n;
  while (counter--) {

    ll l = (ans) / (2 * n) - 5, r = ans / (2 * n);
    if (ans == funny)
      l = 0;
    l = max(l, 0LL);
    while (l != r) {
      ll mid = (l + r) / 2;
      if (check(2 * n * mid + 2 * n - counter - 1))
        r = mid;
      else
        l = mid + 1;
    }
    ans = min(ans, 2 * n * l + 2 * n - counter - 1);
  }
  if (ans == 5e18)
    cout << "-1\n";
  else
    cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}