/*
 * Problem URL : https://codeforces.com/problemset/problem/2122/E
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
int TT, n, i, j, k, a, b, m, dp[510][510], A[510], B[510], mod = 998244353;
main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  for (cin >> TT; TT--;) {
    cin >> n >> k;
    for (i = 1; i <= n; i++)
      cin >> A[i];
    for (i = 1; i <= n; i++)
      cin >> B[i];
    if (n == 1) {
      int ans = 1;
      if (A[1] == -1)
        ans *= k;
      if (B[1] == -1)
        ans *= k;
      cout << ans << "\n";
      continue;
    }
    for (i = 1; i <= n; i++)
      for (j = 0; j <= k; j++)
        dp[i][j] = 0;
    dp[n][0] = 1;
    for (i = n - 1; i >= 1; i--) {
      vector<int> cnt(2 * k), pre(2 * k);
      if (A[i + 1] == -1 && B[i] == -1) {
        for (j = 0; j < 2 * k - 1; j++)
          cnt[j] = k - abs(k - 1 - j);
      } else if (A[i + 1] == -1) {
        for (j = 1; j <= k; j++)
          cnt[j - B[i] + k - 1]++;
      } else if (B[i] == -1) {
        for (j = 1; j <= k; j++)
          cnt[A[i + 1] - j + k - 1]++;
      } else
        cnt[A[i + 1] - B[i] + k - 1]++;
      pre[0] = cnt[0];
      for (j = 1; j < 2 * k; j++)
        pre[j] = pre[j - 1] + cnt[j];
      for (b = 0; b < k; b++)
        dp[i][0] += pre[-b + k - 1] * dp[i + 1][b];
      dp[i][0] %= mod;
      for (b = 1; b <= k; b++) {
        int x = pre[2 * k - 1];
        if (2 * k - b - 2 >= 0)
          x -= pre[2 * k - b - 2];
        dp[i][k] += dp[i + 1][b] * x;
      }
      dp[i][k] %= mod;
      for (a = 1; a < k; a++) {
        for (b = 0; b <= a; b++) {
          dp[i][a] += cnt[a - b + k - 1] * dp[i + 1][b];
        }
        dp[i][a] %= mod;
      }
      // for(a=0;a<=k;a++)cout<<dp[i][a]<<" ";cout<<endl;
    }
    int ans = 0;
    for (j = 0; j <= k; j++)
      ans += dp[1][j];
    ans %= mod;
    if (A[1] == -1)
      ans *= k;
    if (B[n] == -1)
      ans *= k;
    ans %= mod;
    cout << ans << "\n";
  }
}