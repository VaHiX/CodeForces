/*
 * Problem URL : https://codeforces.com/contest/2036/problem/F
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
inline long long f(long long x) {
  switch (x & 3) {
  case 0:
    return x;
  case 1:
    return 1;
  case 2:
    return x + 1;
  default:
    return 0;
  }
}
long long l, r, ans;
int T, x, y;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld%d%d", &l, &r, &x, &y);
    ans = f(r) ^ f(l - 1);
    r = r - y >> x;
    l = (l - y - 1 >> x) + 1;
    if (l < 0)
      l = 0;
    if (r - l + 1 & 1)
      ans ^= y;
    ans ^= (f(r) ^ f(l - 1)) << x;
    printf("%lld\n", ans);
  }
  return 0;
}