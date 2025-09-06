/*
 * Problem URL : https://codeforces.com/problemset/problem/617/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
typedef long long lr;
lr n, a, b, c, d, x, y, mx, mn;
std::pair<lr, lr> p[2020];
int main() {
  scanf("%lld%lld%lld%lld%lld", &n, &a, &b, &c, &d);
  for (lr i = 1; i <= n; ++i)
    scanf("%lld%lld", &x, &y),
        p[i] = std::make_pair((x - a) * (x - a) + (y - b) * (y - b),
                              (x - c) * (x - c) + (y - d) * (y - d));
  std::sort(p + 1, p + 1 + n), mn = p[n].first;
  for (lr i = n; i; --i)
    mx = std::max(mx, p[i].second), mn = std::min(mn, p[i - 1].first + mx);
  return 0 & printf("%lld", mn);
}
