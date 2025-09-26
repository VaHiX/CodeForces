/*
 * Problem URL : https://codeforces.com/problemset/problem/811/C
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

int dp[N], a[N], lef[N], rig[N];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (!lef[a[i]])
      lef[a[i]] = i;
    rig[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1];
    int lim = i, cost = 0;
    for (int j = i; j > 0; j--) {
      lim = min(lim, lef[a[j]]);
      if (rig[a[j]] > i)
        break;
      if (j == rig[a[j]])
        cost ^= a[j];
      if (j == lim) {
        dp[i] = max(dp[i], dp[j - 1] + cost);
      }
    }
  }
  cout << dp[n];
}