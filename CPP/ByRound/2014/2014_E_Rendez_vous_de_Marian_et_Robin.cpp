/*
 * Problem URL : https://codeforces.com/contest/2014/problem/E
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;

void run() {
 int n, m, h; cin >> n >> m >> h;
 vector<bool> horse(n);
 while (h--) {
  int x; cin >> x; horse[x-1] = 1;
 }
 vector<vector<pair<int,int>>> adj(n);
 while (m--) {
  int u, v, w; cin >> u >> v >> w; u--, v--;
  adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
 }

 vector vis(2, vector(2, vector(n, false)));
 priority_queue<tuple<long long,bool,bool,int>> pq;
 pq.emplace(0, 0, 0, 0), pq.emplace(0, 1, 0, n-1);

 while (pq.size()) {
  auto [d, b, ho, u] = pq.top(); pq.pop();
  d = -d;

  if (vis[b][ho][u]) continue;
  if (vis[!b][ho][u] or vis[!b][!ho][u]) {
   cout << d << '\n';
   return;
  }
  vis[b][ho][u] = 1;

  ho |= horse[u];
  for (auto [v, w] : adj[u]) {
   pq.emplace(-(d+(ho?w/2:w)), b, ho, v);
  }
 }

 cout << "-1\n";
}

int main() {
 cin.tie(0)->sync_with_stdio(0);
 int t; cin >> t; while (t--) run();
}