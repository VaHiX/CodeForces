/*
 * Problem URL : https://codeforces.com/problemset/problem/2114/F
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
map<pair<int, int>, int> dp;
int f(int x, int k) {
  if (x == 1)
    return 0;
  if (dp.find(mp(x, k)) != dp.end())
    return dp[{x, k}];
  int bnd = sqrt(x), r = 1e8;
  for (int i = 1; i <= bnd; ++i) {
    if (x % i)
      continue;
    int j = x / i;
    if (1 < i && i <= k)
      r = min(r, f(x / i, k) + 1);
    if (1 < j && j <= k)
      r = min(r, f(x / j, k) + 1);
  }
  return dp[{x, k}] = r;
}
signed main() {
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    int x, y, k;
    scanf("%d %d %d", &x, &y, &k);
    int g = __gcd(x, y), a = f(x / g, k) + f(y / g, k);
    a >= 1e8 ? puts("-1") : printf("%d\n", a);
  }
}