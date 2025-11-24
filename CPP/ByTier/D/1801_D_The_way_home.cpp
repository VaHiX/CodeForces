// Problem: CF 1801 D - The way home
// https://codeforces.com/contest/1801/problem/D

/*
Algorithm: Dijkstra-like approach with dynamic programming
Time Complexity: O((n + m) * log(n * n)) where n is number of cities and m is number of flights
Space Complexity: O(n * n) for the dp and ost arrays

This solution uses a modified Dijkstra's algorithm with state (city, max profit city so far).
The state represents the minimum number of performances needed to reach a city with a certain maximum profit city.
*/
#include <stdint.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
const int MAX = 800 + 7;
const int mod = 1e9 + 7;
#define int long long
vector<pair<int, int>> g[MAX];
bool good = false;
vector<bool> was(MAX, false);
int n;
void dfs(int v) {
  if (was[v])
    return;
  was[v] = true;
  if (v == n)
    good = true;
  for (auto to : g[v])
    dfs(to.first);
}
void solve() {
  int m, p, GG;
  cin >> n >> m >> p;
  good = false;
  vector<ll> a(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i], g[i].clear(), was[i] = false;
  for (int i = 1; i <= m; i++) {
    int v, u, w;
    cin >> v >> u >> w;
    g[v].push_back({u, w});
  }
  dfs(1);
  if (!good) {
    cout << -1 << '\n';
    return;
  }
  ll dp[n + 1][n + 1];
  ll ost[n + 1][n + 1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = 1e18;
      ost[i][j] = 0;
    }
  }
  set<pair<pair<int, int>, array<int, 3>>> q;
  dp[1][1] = 0;
  ost[1][1] = p;
  q.insert({{0, p}, {1, 1, p}});
  int res = 1e18;
  while ((int)(q.size())) {
    array<int, 3> rq = q.begin()->second;
    q.erase(q.begin());
    int v = rq[0];
    int mx = rq[1];
    int have = rq[2];
    if (v == n) {
      cout << dp[v][mx] << '\n';
      return;
    }
    for (auto toto : g[v]) {
      int to = toto.first;
      int cost = toto.second;
      int nhave = have;
      int nmx = mx;
      if (a[to] > a[mx])
        nmx = to;
      if (cost <= nhave) {
        nhave -= cost;
        if (dp[to][nmx] > dp[v][mx]) {
          q.erase({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
          dp[to][nmx] = dp[v][mx];
          ost[to][nmx] = nhave;
          q.insert({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
        }
        if (dp[to][nmx] == dp[v][mx] && ost[to][nmx] < nhave) {
          q.erase({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
          dp[to][nmx] = dp[v][mx];
          ost[to][nmx] = nhave;
          q.insert({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
        }
      } else {
        cost -= nhave;
        nhave = 0;
        int need = (cost + a[mx] - 1) / a[mx];
        nhave = a[mx] * need - cost;
        if (dp[to][nmx] > dp[v][mx] + need) {
          q.erase({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
          dp[to][nmx] = dp[v][mx] + need;
          ost[to][nmx] = nhave;
          q.insert({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
        }
        if (dp[to][nmx] == dp[v][mx] + need && ost[to][nmx] < nhave) {
          q.erase({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
          dp[to][nmx] = dp[v][mx] + need;
          ost[to][nmx] = nhave;
          q.insert({{dp[to][nmx], -ost[to][nmx]}, {to, nmx, ost[to][nmx]}});
        }
      }
    }
  }
}
int32_t main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/