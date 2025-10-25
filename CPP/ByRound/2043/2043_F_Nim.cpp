/*
 * Problem URL : https://codeforces.com/contest/2043/problem/F
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, Mod = 998244353;
inline int add(int a, int b) { return a + b >= Mod ? a + b - Mod : a + b; }
int n, q, a[N], sum[55][N], cnt[55], f[65], g[65], tf[65], tg[65];
pair<int, int> solve() {
  memset(f, 0x3f, sizeof(f));
  memset(g, 0, sizeof(g));

  for (int i = 1; i <= 50; ++i) {
    if (!cnt[i])
      continue;
    tf[i] = 1, tg[i] = 1;
    for (int j = 1; j <= 63; ++j) {
      if (f[j ^ i] > f[j] + 1)
        tf[j ^ i] = f[j] + 1, tg[j ^ i] = g[j];
      else if (f[j ^ i] == f[j] + 1)
        tf[j ^ i] = f[j ^ i], tg[j ^ i] = add(g[j ^ i], g[j]);
      else
        tf[j ^ i] = f[j ^ i], tg[j ^ i] = g[j ^ i];
    }
    memcpy(f, tf, sizeof(f)), memcpy(g, tg, sizeof(tg));
  }
  return make_pair(f[0], g[0]);
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], sum[a[i]][i] = 1;
  for (int i = 0; i <= 50; ++i)
    for (int j = 1; j <= n; ++j)
      sum[i][j] += sum[i][j - 1];
  while (q--) {
    int l, r;
    cin >> l >> r;
    for (int i = 0; i <= 50; ++i)
      cnt[i] = sum[i][r] - sum[i][l - 1];
    if (cnt[0]) {
      cout << r - l << " " << cnt[0] << endl;
      continue;
    }
    int num = 0, flg = 0;
    for (int i = 1; i <= 50; ++i)
      if (cnt[i] >= 2)
        num = add(num, 1ll * cnt[i] * (cnt[i] - 1) / 2 % Mod), flg = 1;
    if (flg)
      cout << r - l - 1 << " " << num << endl;
    else {
      auto ans = solve();
      if (ans.first > 1e9)
        cout << -1 << endl;
      else
        cout << r - l + 1 - ans.first << " " << ans.second << endl;
    }
  }
  return 0;
}