/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/F2
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using iii = tuple<int, int, int>;

#define pb push_back
#define eb emplace_back
#define mp make_pair

int tc, n, dp[400005], p0[400005], ps[400005], lft[400005][2], rigz[400005][2],
    cry[400005], cry2[400005], cry3[400005], cry4[400005];
bool is_good[400005][2];
string s, t;

struct ds {
  vector<ii> vec;
  void insert(int x, int y) {
    if (vec.empty()) {
      vec.eb(x, y);
      return;
    }
    if (vec.back().first == x) {
      if (vec.back().second < y) {
        return;
      }
      vec.pop_back();
    }
    while (!vec.empty() && vec.back().second >= y) {
      vec.pop_back();
    }
    vec.eb(x, y);
  }
  int qry(int x) {
    auto it = upper_bound(vec.begin(), vec.end(), mp(x, (int)2e9));
    if (it == vec.end()) {
      return (int)2e9;
    } else {
      return it->second;
    }
  }
  void clear() { vec.clear(); }
} val0[800005], val1[800005];

void upd(int x, int y, int v, ds val[]) {
  for (x += n + 1; x > 0; x >>= 1) {
    val[x].insert(y, v);
  }
  val[0].insert(y, v);
}

int qry(int x, int y, ds val[]) {
  int r = n;
  int ret = (int)2e9;
  for (x += n + 2, r += n + 2; x < r; x >>= 1, r >>= 1) {
    if (x & 1) {
      ret = min(ret, val[x++].qry(y));
    }
    if (r & 1) {
      ret = min(ret, val[--r].qry(y));
    }
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> tc;
  while (tc--) {
    cin >> s >> t;
    n = s.size();
    for (int i = 0; i < n; i++) {
      p0[i] = (i ? p0[i - 1] : 0) + (s[i] == '0');
      ps[i] = (i ? ps[i - 1] + (s[i] != s[i - 1]) : 0);
      for (int j : {0, 1}) {
        if (t[i] == 1 - j + '0') {
          lft[i][j] = i;
        } else {
          lft[i][j] = (i ? lft[i - 1][j] : -1);
        }
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int j : {0, 1}) {
        if (t[i] == 1 - j + '0') {
          rigz[i][j] = i;
        } else {
          rigz[i][j] = (i + 1 < n ? rigz[i + 1][j] : n);
        }
      }
    }
    for (int j = 0; j < n; j++) {
      is_good[j][0] =
          (j == 0 || s[j - 1] != s[j]) && (j == 0 || s[j - 1] != '1');
      is_good[j][1] =
          (j == 0 || s[j - 1] != s[j]) && (j == 0 || s[j - 1] != '0');
      cry[j] = rigz[j][0] - j + (j ? p0[j - 1] : 0);
      cry2[j] = j - (j ? p0[j - 1] : 0);
      cry3[j] = rigz[j][1] - (j ? p0[j - 1] : 0);
      cry4[j] = (j ? p0[j - 1] : 0);
    }
    int lim = 0;
    for (int i = 0; i < n; i++) {
      dp[i] = (int)1e9;
      if (i > 0 && s[i] != s[i - 1]) {
        for (int j = lim; j < i; j++) {
          if (is_good[j][0]) {
            upd(cry3[j], cry4[j], 2 * (j ? dp[j - 1] : 0) - ps[j], val0);
          }
          if (is_good[j][1]) {
            upd(cry[j], cry2[j], 2 * (j ? dp[j - 1] : 0) - ps[j], val1);
          }
        }
        lim = i;
      }
      if (s[i] == t[i] || t[i] == '?') {
        dp[i] = (i ? dp[i - 1] : 0);
      }
      if (!(i == n - 1 || s[i] != s[i + 1])) {
        continue;
      }
      if (!(t[i] != '?' && t[i] != '0')) {
        dp[i] = min(
            dp[i],
            (qry(i - p0[i], lft[i][0] - i - 1 + p0[i], val0) + ps[i] + 1) / 2 +
                (s[i] == '0'));
      }
      if (!(t[i] != '?' && t[i] != '1')) {
        dp[i] = min(dp[i],
                    (qry(p0[i] - 1, lft[i][1] - p0[i], val1) + ps[i] + 1) / 2 +
                        (s[i] == '1'));
      }
    }
    cout << (dp[n - 1] >= (int)1e9 ? -1 : dp[n - 1]) << '\n';
    for (int i = 0; i < 2 * (n + 1); i++) {
      val0[i].clear();
      val1[i].clear();
    }
  }
}