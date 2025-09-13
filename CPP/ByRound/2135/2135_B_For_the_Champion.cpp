/*
 * Problem URL : https://codeforces.com/contest/2135/problem/B
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
constexpr long long inf = 1e9;
int t, n, x[105], y[105], w1, w2;
long long t1, t2, t3, val1, val2;
int main() {
  cin >> t;
  while (t--) {
    scanf("%d", &n), w1 = w2 = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &x[i], &y[i]);
      if (!w1 || x[i] + y[i] > x[w1] + y[w1])
        w1 = i;
      if (!w2 || x[i] - y[i] > x[w2] - y[w2])
        w2 = i;
    }
    printf("? U %lld\n? U %lld\n? R %lld\n? R %lld\n", inf, inf, inf, inf),
        fflush(stdout);
    scanf("%lld%lld%lld%lld", &t1, &t2, &t3, &val1),
        val1 += x[w1] + y[w1] - 4 * inf;
    printf("? D %lld\n? D %lld\n? D %lld\n? D %lld\n", inf, inf, inf, inf),
        fflush(stdout);
    scanf("%lld%lld%lld%lld", &t1, &t2, &t3, &val2),
        val2 += x[w2] - y[w2] - 4 * inf;
    printf("! %lld %lld\n", (val1 + val2) / 2, (val1 - val2) / 2),
        fflush(stdout);
  }
  return 0;
}