/*
 * Problem URL : https://codeforces.com/contest/2140/problem/C
 * Submit Date : 2025-09-09
 */

#include <algorithm>
#include <stdio.h>

using namespace std;
const int maxn = 2e5 + 7;
#define int long long
int t, n, a[maxn];
signed main() {
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &a[i]);
    }
    int minn = 1e18, ans, sum = 0;
    if (n & 1)
      ans = n - 1;
    else
      ans = n - 2;
    for (int i = 1; i <= n; i++) {
      if (i & 1)
        minn = min(minn, a[i] * 2 + i), sum += a[i];
      else
        ans = max(ans, a[i] * 2 + i - minn), sum -= a[i];
    }
    minn = 1e18;
    for (int i = n; i; i--) {
      if (i & 1)
        minn = min(minn, a[i] * 2 - i);
      else
        ans = max(ans, a[i] * 2 - i - minn);
    }
    printf("%lld\n", ans + sum);
  }
  return 0;
}