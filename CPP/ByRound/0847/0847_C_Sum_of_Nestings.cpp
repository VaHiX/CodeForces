/*
 * Problem URL : https://codeforces.com/contest/847/problem/C
 * Submit Date : 2025-08-31
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll n, k;
  scanf("%lld %lld", &n, &k);
  if (n * (n - 1) / 2 < k) {
    puts("Impossible");
  } else {
    ll cur(0);
    for (ll p = 1; p <= 2 * n; p++) {
      if (cur <= k) {
        k -= cur;
        ++cur;
        putchar('(');
      } else {
        --cur;
        putchar(')');
      }
    }
  }

  return 0;
}
