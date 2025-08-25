/*
 * Problem URL : https://codeforces.com/problemset/problem/2109/E
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
constexpr int mod = 998244353;
int t, n, k, dp[505][505], C[505][505];
string s;
inline int mo(int x) { return x >= mod ? x - mod : x; }
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> t;
  C[0][0] = 1;
  for (int i = 1; i <= 500; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = mo(C[i - 1][j - 1] + C[i - 1][j]);
  }
  while (t--) {
    cin >> n >> k >> s;
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= k; j++)
        dp[i][j] = 0;
    dp[n][0] = 1;
    for (int i = n - 1; ~i; i--) {
      for (int j = 0; j <= k; j++) {
        int tot = j + (s[i] == '0'), r = min(k - j, tot);
        for (int l = 0; l <= r; l++)
          dp[i][j + l] =
              (dp[i][j + l] + (long long)dp[i + 1][j] * C[(tot + l) / 2][l]) %
              mod;
      }
    }
    cout << dp[0][k] << '\n';
  }
  return 0;
}