/*
 * Problem URL : https://codeforces.com/problemset/problem/2130/F
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
constexpr int mod = 998244353;
ll n;
ll dp[110][110][12][12], C[110][110], suml[110][110][12], sumr[110][110][12];
ll s[110];
void solve() {
  cin >> n;
  bool o = false;
  ll sum = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> s[i];
    sum += s[i];
    if (s[i] >= 12)
      o = true;
  }
  if (o || sum > n - 1) {
    cout << 0 << endl;
    return;
  }
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= n + 1; ++j) {
      memset(suml[i][j], 0, sizeof(suml[i][j]));
      memset(sumr[i][j], 0, sizeof(sumr[i][j]));
    }
  }
  for (int len = 1; len <= n + 1; ++len)
    for (int l = 0; l + len <= n + 1; ++l)
      for (int x = 0; x < 12; ++x)
        for (int y = 0; y < 12; ++y) {
          int r = l + len;
          if (x + y > r - l + 1) {
            dp[l][r][x][y] = 0;
            continue;
          }
          if (l + 1 == r) {
            dp[l][r][x][y] = ((x == 0 && y == 0) ? 1 : 0);
            suml[l][r][x] = (suml[l][r][x] + dp[l][r][x][y]) % mod;
            sumr[l][r][y] = (sumr[l][r][y] + dp[l][r][x][y]) % mod;
            continue;
          }
          ll ans = 0;
          for (int i = l + 1; i <= r - 1; ++i) {
            if (s[i] != -1) {
              for (int j = 0; j <= s[i]; ++j) {
                if (i - l <= r - i && l != 0 || r == n + 1) {
                  if (x > 0)
                    ans = (ans + C[r - l - 2][i - l - 1] * dp[l][i][x - 1][j] %
                                     mod * dp[i][r][s[i] - j][y]) %
                          mod;
                } else {
                  if (y > 0)
                    ans = (ans + C[r - l - 2][i - l - 1] * dp[l][i][x][j] %
                                     mod * dp[i][r][s[i] - j][y - 1]) %
                          mod;
                }
              }
            } else {
              if (i - l <= r - i && l != 0 || r == n + 1) {
                if (x > 0)
                  ans = (ans + C[r - l - 2][i - l - 1] * suml[l][i][x - 1] %
                                   mod * sumr[i][r][y]) %
                        mod;
              } else {
                if (y > 0)
                  ans = (ans + C[r - l - 2][i - l - 1] * suml[l][i][x] % mod *
                                   sumr[i][r][y - 1]) %
                        mod;
              }
            }
          }
          dp[l][r][x][y] = ans;
          suml[l][r][x] = (suml[l][r][x] + dp[l][r][x][y]) % mod;
          sumr[l][r][y] = (sumr[l][r][y] + dp[l][r][x][y]) % mod;
        }
  ll ans = 0;
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j) {
      ans = (ans + dp[0][n + 1][i][j]) % mod;
    }
  cout << ans << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  C[0][0] = 1;
  for (int i = 1; i <= 105; ++i)
    for (int j = 0; j <= i; ++j) {
      if (j == 0)
        C[i][j] = 1;
      else
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
  int tt;
  cin >> tt;
  while (tt--) {
    solve();
  }
}