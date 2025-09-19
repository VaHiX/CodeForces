/*
 * Problem URL : https://codeforces.com/problemset/problem/2074/G
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int N, A[400];
long long dp[400][401];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (; T--;) {
    cin >> N;
    for (int i = 0; i < N; i++)
      cin >> A[i];
    for (int l = 0; l < N; l++)
      for (int r = l; r <= N; r++)
        dp[l][r] = 0;
    for (int k = 3; k <= N; k++)
      for (int l = 0; l + k <= N; l++) {
        int r = l + k;
        long long cur = max(dp[l + 1][r], dp[l][r - 1]);
        for (int m = l + 1; m < r; m++) {
          cur = max(cur, dp[l][m] + dp[m][r]);
          if (m < r - 1)
            cur = max(cur,
                      dp[l + 1][m] + dp[m + 1][r - 1] + A[l] * A[m] * A[r - 1]);
        }
        dp[l][r] = cur;
      }
    cout << dp[0][N] << "\n";
  }
}