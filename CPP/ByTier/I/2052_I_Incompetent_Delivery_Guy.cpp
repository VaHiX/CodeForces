/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::array<int, 2>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v, t;
    std::cin >> u >> v >> t;
    u--;
    v--;
    adj[v].push_back({u, t});
  }

  std::vector<long long> dis(n, -1);
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>,
                      std::greater<std::pair<long long, int>>>
      pq;
  pq.push({0ll, n - 1});
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (dis[u] != -1) {
      continue;
    }
    dis[u] = d;

    for (auto [v, w] : adj[u]) {
      pq.push({d + w, v});
    }
  }

  std::vector<int> dp(n, -1);
  std::deque<std::array<int, 2>> dq;
  for (int i = 0; i < n; i++) {
    if (dis[i] == -1) {
      dq.push_back({i, 0});
    }
  }

  std::vector<int> in(n);
  for (int u = 0; u < n; u++) {
    if (dis[u] == -1) {
      continue;
    }
    for (auto [v, w] : adj[u]) {
      if (dis[v] == dis[u] + w) {
        in[v]++;
      }
    }
  }
  while (!dq.empty()) {
    auto [u, d] = dq.front();
    dq.pop_front();

    if (u == n - 1 || dp[u] != -1) {
      continue;
    }
    dp[u] = d;

    for (auto [v, w] : adj[u]) {
      dq.push_back({v, d + 1});
      if (dis[u] != -1 && dis[v] == dis[u] + w) {
        if (--in[v] == 0) {
          dq.push_front({v, d});
        }
      }
    }
  }

  if (dp[0] == -1) {
    dp[0] = n + 1;
  }
  std::cout << dp[0] - 1 << "\n";
  return 0;
}