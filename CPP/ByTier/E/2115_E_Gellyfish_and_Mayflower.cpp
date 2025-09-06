/*
 * Problem URL : https://codeforces.com/problemset/problem/2115/E
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
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
    small[t] = small[t - 1];
    for (int i = 0; i < n; ++i) {
      if (t >= c[i]) {
        long long cand = small[t - c[i]][i] + w[i];
        small[t][i] = max(small[t][i], cand);
      }
      for (int j : rev[i]) {
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
      answer[i] = small[r][p];
    }
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    long long lhs = 1LL * w[i] * c[j];
    long long rhs = 1LL * w[j] * c[i];
    if (lhs != rhs)
      return lhs < rhs;
    return i < j;
  });

  vector<char> valid(n, 0);

  for (int best : order) {
    valid[best] = 1;
    if (!valid[0])
      continue;

    int C = c[best], W = w[best];
    vector<vector<long long>> cycs(n);
    cycs[0] = vector<long long>(C, LLONG_MIN / 4);
    cycs[0][0] = 0;

    for (int i = 0; i < n; ++i) {
      if (!valid[i])
        continue;
      for (int j : rev[i]) {
        if (i > best && j < best)
          continue;
        if (cycs[j].empty())
          continue;
        if (cycs[i].empty()) {
          cycs[i] = cycs[j];
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
        while (vis[cur] < 2) {
          vis[cur]++;
          int nxt = cur + c[i];
          long long blocks = nxt / C;
          int rem = nxt % C;
          long long cand = cycs[i][cur] + w[i] - blocks * W;
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
        continue;
      long long full = r / C;
      int rem = r % C;
      long long cand = tbl[rem] + full * W;
      answer[idx] = max(answer[idx], cand);
    }
  }

  for (int i = 0; i < q; ++i) {
    cout << answer[i] << (i + 1 < q ? ' ' : '\n');
  }
  return 0;
}