/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, mod = 998244353;
char c[1001000];
int n;
int dp[1010000], dp2[2001000], all;
void sol() {
  scanf("%s", c + 1);
  n = strlen(c + 1);
  reverse(c + 1, c + n + 1);
  for (int i = 0; i <= n; i++)
    dp[i] = 0;
  c[0] = '1', dp[0] = 1, all = 1;
  int ans = 0;
  for (int i = 0; i <= n; i++)
    if (c[i] == '1') {
      int d = i + 1, s = 0;
      while (d <= n && c[d] == '0')
        d++, s++;
      (ans += 1ll * all * (s + 1) % mod) %= mod;
      if (!s)
        continue;
      for (int k = 1, z = 0; k <= s; k++)
        (z += dp[k - 1]) %= mod, dp2[k] = z;
      for (int j = 1; j <= s; j++)
        (dp[j] += dp2[j]) %= mod, (all += dp2[j]) %= mod;
    }
  printf("%d\n", (ans + mod - 1) % mod);
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}