/*
 * Problem URL : https://codeforces.com/contest/2033/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
std::map<long long, int> mp;
int dp[100005];
int T, n;
long long s;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    mp.clear();
    mp[0] = 0;
    s = 0;
    for (int i = 1, x; i <= n; ++i) {
      scanf("%d", &x);
      s += x;
      dp[i] = dp[i - 1];
      if (mp.count(s))
        dp[i] = std::max(dp[i], dp[mp[s]] + 1);
      mp[s] = i;
    }
    printf("%d\n", dp[n]);
  }
  return 0;
}