/*
 * Problem URL : https://codeforces.com/problemset/problem/1217/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, n;
    scanf("%lld %lld %lld", &a, &b, &n);
    ll tmp = a + n - b - 1;
    if (tmp < 0) {
      puts("0");
    } else {
      printf("%lld\n", 1 + (((tmp / 2) < n) ? (tmp / 2) : n));
    }
  }

  return 0;
}
