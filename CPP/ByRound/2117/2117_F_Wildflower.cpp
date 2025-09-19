/*
 * Problem URL : https://codeforces.com/problemset/problem/2117/F
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMaxN = 2e5 + 1, mod = 1e9 + 7;

int t, n, c, o, p, q, ans;
vector<int> e[kMaxN];

void dfs(int x, int f, int d) {
  e[x].size() == (f > 0) && (c++, o = d, p += d),
      e[x].size() == 2 + (f > 0) && (q = d);
  for (int i : e[x]) {
    if (i != f) {
      dfs(i, x, d + 1);
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n, p = c = 0;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y, e[x].push_back(y), e[y].push_back(x);
    }
    dfs(1, 0, 1);
    if (c > 2) {
      ans = 0;
    } else if (c == 1) {
      ans = 1;
      for (int i = 1; i <= n; i++) {
        ans *= 2, ans >= mod && (ans -= mod);
      }
    } else {
      p -= o, ans = 1;
      for (int i = 1; i <= q + max(0, abs(o - p) - 1); i++) {
        ans *= 2, ans >= mod && (ans -= mod);
      }
      ans = ans * (o != p ? 3ll : 2ll) % mod;
    }
    cout << ans << '\n', fill(e + 1, e + n + 1, vector<int>());
  }
  return 0;
}