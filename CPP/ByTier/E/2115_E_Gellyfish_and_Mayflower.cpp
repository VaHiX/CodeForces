// Problem: CF 2115 E - Gellyfish and Mayflower
// https://codeforces.com/contest/2115/problem/E

/*
E. Gellyfish and Mayflower
Purpose: Solve a directed acyclic graph (DAG) problem where we need to determine the maximum total power of cards that can be collected from vertices, subject to constraints of coin usage and vertex traversal.

Algorithms/Techniques:
- Dynamic Programming with precomputed small value table
- Cyclical optimization using modular arithmetic
- Topological sorting by ratio of weight/cost

Time Complexity:
O(n^2 * MAXC^2 + q * n) where MAXC = max(c[i]) <= 200

Space Complexity:
O(MAXC^2 * n + q) where MAXC = max(c[i]) <= 200
*/

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> c(n), w(n);
  for (int i = 0; i < n; ++i) {
    cin >> c[i] >> w[i];
  }
  vector<vector<int>> rev(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    rev[b].push_back(a);
  }
  int MC = *max_element(c.begin(), c.end());
  int MAXT = MC * MC;
  vector<vector<long long>> small(MAXT + 1, vector<long long>(n, 0LL));
  for (int t = 1; t <= MAXT; ++t) {
    small[t] = small[t - 1]; // Copy the previous state.
    for (int i = 0; i < n; ++i) {
      if (t >= c[i]) { // If we have enough coins to buy a card at vertex i
        long long cand = small[t - c[i]][i] + w[i];
        small[t][i] = max(small[t][i], cand); // Update with better option.
      }
      for (int j : rev[i]) { // Propagate from previous vertices
        small[t][i] = max(small[t][i], small[t][j]);
      }
    }
  }
  int q;
  cin >> q;
  vector<pair<int, long long>> queries(q);
  for (int i = 0; i < q; ++i) {
    cin >> queries[i].first >> queries[i].second;
    --queries[i].first;
  }
  vector<long long> answer(q, -1LL);
  for (int i = 0; i < q; ++i) {
    int p = queries[i].first;
    long long r = queries[i].second;
    if (r <= MAXT) {
      answer[i] = small[r][p]; // Direct lookup for small coin amounts
    }
  }
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    long long lhs = 1LL * w[i] * c[j];
    long long rhs = 1LL * w[j] * c[i];
    if (lhs != rhs)
      return lhs < rhs; // Sort by ratio of power to cost
    return i < j;
  });
  vector<char> valid(n, 0);
  for (int best : order) {
    valid[best] = 1;
    if (!valid[0])
      continue;
    int C = c[best], W = w[best]; // C is capacity, W is weight.
    vector<vector<long long>> cycs(n);
    cycs[0] = vector<long long>(C, LLONG_MIN / 4);
    cycs[0][0] = 0;
    for (int i = 0; i < n; ++i) {
      if (!valid[i])
        continue;
      for (int j : rev[i]) { // Process all predecessors
        if (i > best && j < best)
          continue; // Skip invalid transitions
        if (cycs[j].empty())
          continue;
        if (cycs[i].empty()) {
          cycs[i] = cycs[j]; // Inherit value from parent
        } else {
          for (int t = 0; t < C; ++t) {
            cycs[i][t] = max(cycs[i][t], cycs[j][t]);
          }
        }
      }
      if (cycs[i].empty())
        continue;
      vector<int> vis(C, 0);
      for (int start = 0; start < C; ++start) {
        int cur = start;
        while (vis[cur] < 2) { // Loop detection
          vis[cur]++;
          int nxt = cur + c[i];
          long long blocks = nxt / C;
          int rem = nxt % C;
          long long cand = cycs[i][cur] + w[i] - blocks * W; // Cost of buying card
          cycs[i][rem] = max(cycs[i][rem], cand);
          cur = rem;
        }
      }
      for (int t = 1; t < C; ++t) {
        cycs[i][t] = max(cycs[i][t], cycs[i][t - 1]);
      }
    }
    for (int idx = 0; idx < q; ++idx) {
      int p = queries[idx].first;
      long long r = queries[idx].second;
      if (p < best)
        continue;
      auto &tbl = cycs[p];
      if (tbl.empty() || r < 1LL * MC * C)
        continue; // Skip if not enough coins for the cycle
      long long full = r / C; // How many complete cycles we can do
      int rem = r % C;
      long long cand = tbl[rem] + full * W; // Final value with complete cycle
      answer[idx] = max(answer[idx], cand);
    }
  }
  for (int i = 0; i < q; ++i) {
    cout << answer[i] << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/