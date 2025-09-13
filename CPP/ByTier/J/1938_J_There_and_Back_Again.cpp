/*
 * Problem URL : https://codeforces.com/contest/1938/problem/J
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
const int INF = 2e8;

struct edge {
  int a, b, c;
  edge(int a, int b, int c) : a(a), b(b), c(c) {}
};
int n, m;
vector<edge> adj[101010];
bool vst[303030];
int dst[101010];
int par[101010];
int e[303030][4];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    auto &[u, v, t, idx] = e[i];
    cin >> u >> v >> t;
    idx = i;
    adj[u].emplace_back(v, t, i);
    adj[v].emplace_back(u, t, i);
  }
  for (int i = 2; i <= n; ++i) {
    dst[i] = INF;
  }
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push(pair<int, int>(0, 1));
  while (!pq.empty()) {
    auto [d, cur] = pq.top();
    pq.pop();
    if (dst[cur] != d)
      continue;
    for (auto [nxt, t, i] : adj[cur]) {
      if (dst[nxt] > d + t) {
        dst[nxt] = d + t;
        pq.push(pair<int, int>(d + t, nxt));
        par[nxt] = i;
      }
    }
  }
  if (dst[n] == INF) {
    cout << -1;
    return 0;
  }
  for (int cur = n; cur != 1;) {
    auto [u, v, t, i] = e[par[cur]];
    vst[i] = 1;
    cur ^= u ^ v;
  }
  e[0][0] = 1;
  int ans = INF;
  for (int cur = n; cur != 0;) {
    for (auto [nxt, t, i] : adj[cur]) {
      if (vst[i])
        continue;
      ans = min(ans, dst[n] + 2 * t);
      ans = min(ans, dst[n] - dst[cur] + t + dst[nxt]);
    }
    auto [u, v, t, i] = e[par[cur]];
    cur ^= u ^ v;
  }
  if (ans == INF)
    cout << -1;
  else
    cout << dst[n] + ans;
}