// Problem: CF 2066 F - Curse
// https://codeforces.com/contest/2066/problem/F

#include <assert.h>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
const int INF = 1e9;
const int N = 505;
using BS = bitset<N>;
const BS ONE = BS().set();
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x : a)
      cin >> x;
    for (auto &x : b)
      cin >> x;
    vector<int> as(n + 1), bs(m + 1);
    for (int i = 0; i < n; i++) {
      as[i + 1] = as[i] + a[i];
    }
    for (int i = 0; i < m; i++) {
      bs[i + 1] = bs[i] + b[i];
    }
    vector<vector<int>> bmax(m + 1, vector<int>(m + 1, -INF));
    for (int r = 1; r <= m; r++) {
      for (int l = r - 1; l >= 0; l--) {
        bmax[l][r] = max({bs[r] - bs[l], bmax[l][r - 1], bmax[l + 1][r]});
      }
    }
    vector<tuple<int, int, int>> asplit;
    auto split = [&](auto &&self, int l, int r) {
      if (l == r)
        return;
      tuple<int, int, int> best = {-1, -1, -INF};
      for (int l2 = l; l2 < r; l2++) {
        for (int r2 = l2 + 1; r2 <= r; r2++) {
          int s = as[r2] - as[l2];
          if (s > get<2>(best)) {
            best = {l2, r2, s};
          } else if (s == get<2>(best) &&
                     r2 - l2 > get<1>(best) - get<0>(best)) {
            best = {l2, r2, s};
          }
        }
      }
      asplit.emplace_back(best);
      self(self, l, get<0>(best));
      self(self, get<1>(best), r);
    };
    split(split, 0, n);
    sort(asplit.begin(), asplit.end());
    vector<int> svals;
    for (auto &[l, r, s] : asplit) {
      svals.push_back(s);
    }
    sort(svals.begin(), svals.end());
    svals.erase(unique(svals.begin(), svals.end()), svals.end());
    vector<vector<int>> lcp(n + 1, vector<int>(m + 1));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        lcp[i][j] = (a[i] == b[j] ? lcp[i + 1][j + 1] + 1 : 0);
      }
    }
    auto ans = [&]() -> optional<vector<tuple<int, int, int, int>>> {
      int k = asplit.size();
      vector<int> cutoffs(m);
      vector<BS> match(k);
      for (int i = 0; i < k; i++) {
        for (int j = 0; j < m; j++) {
          if (lcp[get<0>(asplit[i])][j] >=
              get<1>(asplit[i]) - get<0>(asplit[i])) {
            match[i][j] = 1;
          }
        }
      }
      for (int s : svals) {
        for (int j = 0; j < m; j++) {
          while (cutoffs[j] <= m && bmax[j][cutoffs[j]] <= s) {
            cutoffs[j]++;
          }
          assert(cutoffs[j] >= j + 1);
        }
        vector dp(2, vector<BS>(k + 1));
        dp[0][0][0] = 1;
        for (int used = 0; used < 2; used++) {
          for (int i = 0; i < k; i++) {
            if (get<2>(asplit[i]) >= s) {
              for (int j = i; j < m; j++) {
                if (dp[used][i][j]) {
                  dp[used][i + 1] |= (ONE << (j + 1)) & ~(ONE << cutoffs[j]);
                  if (used == 0) {
                    dp[1][i + 1] |= (ONE << cutoffs[j]);
                  }
                }
              }
            } else {
              dp[used][i + 1] = (dp[used][i] & match[i])
                                << (get<1>(asplit[i]) - get<0>(asplit[i]));
            }
          }
        }
        for (int z = 0; z < 2; z++) {
          if (dp[z][k][m]) {
            pair<int, int> state = {z, m};
            vector<tuple<int, int, int, int>> res;
            for (int i = k - 1; i >= 0; i--) {
              pair<int, int> nstate = {-1, -1};
              if (get<2>(asplit[i]) < s) {
                nstate = make_pair(state.first,
                                   state.second -
                                       (get<1>(asplit[i]) - get<0>(asplit[i])));
              } else {
                for (int j = state.second - 1;
                     j >= 0 && bmax[j][state.second] <= s; j--) {
                  if (dp[state.first][i][j])
                    nstate = make_pair(state.first, j);
                }
                if (state.first == 1) {
                  for (int j = 0; j < state.second && bmax[j][state.second] > s;
                       j++) {
                    if (dp[0][i][j])
                      nstate = make_pair(0, j);
                  }
                }
              }
              assert(nstate.second != -1);
              if (get<2>(asplit[i]) >= s) {
                res.emplace_back(get<0>(asplit[i]), get<1>(asplit[i]),
                                 nstate.second, state.second);
              }
              state = nstate;
            }
            return res;
          }
        }
      }
      return nullopt;
    }();
    if (!ans) {
      cout << "-1\n";
      continue;
    }
    vector<tuple<int, int, int, int>> res = *ans;
    sort(res.begin(), res.end(), [&](const auto &x, const auto &y) {
      auto [lx, rx, _1, _2] = x;
      auto [ly, ry, _3, _4] = y;
      return as[rx] - as[lx] > as[ry] - as[ly];
    });
    int k = res.size();
    cout << 2 * k << '\n';
    int s = as[get<1>(res.back())] - as[get<0>(res.back())];
    for (int i = 0; i < k; i++) {
      auto [l, r, _1, _2] = res[i];
      cout << l + 1 << ' ' << r << ' ' << 1 << ' ' << s << '\n';
      for (auto &[lx, rx, ly, ry] : res) {
        if (lx == l && rx == r) {
          rx = lx + 1;
        } else if (lx > l) {
          lx -= (r - l - 1);
          rx -= (r - l - 1);
        }
      }
    }
    sort(res.begin(), res.end(), [&](const auto &x, const auto &y) {
      auto [_1, _2, lx, rx] = x;
      auto [_3, _4, ly, ry] = y;
      return bmax[lx][rx] < bmax[ly][ry];
    });
    for (int i = 0; i < k; i++) {
      auto [lx, rx, ly, ry] = res[i];
      cout << lx + 1 << ' ' << rx << ' ' << ry - ly;
      for (int j = ly; j < ry; j++) {
        cout << ' ' << b[j];
      }
      cout << '\n';
      for (auto &[lx2, rx2, _1, _2] : res) {
        if (lx2 == lx && rx2 == rx) {
          rx2 += ry - ly - 1;
        } else if (lx2 > lx) {
          lx2 += ry - ly - 1;
          rx2 += ry - ly - 1;
        }
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/