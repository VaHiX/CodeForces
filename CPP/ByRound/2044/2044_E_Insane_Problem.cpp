/*
 * Problem URL : https://codeforces.com/contest/2044/problem/E
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;

int t, k, l1, r1, l2, r2;
long long ans;

int main() {
  scanf("%d", &t);
  for (; t--;) {
    scanf("%d%d%d%d%d", &k, &l1, &r1, &l2, &r2);
    ans = 0;
    for (long long i = 1; i <= r2; i *= k) {
      long long l = max(0ll + l2, i * l1), r = min(0ll + r2, i * r1);
      if (l <= r)
        ans += 1ll * r / i - 1ll * (l - 1) / i;
    }
    printf("%lld\n", ans);
  }
}