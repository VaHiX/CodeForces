/*
 * Problem URL : https://codeforces.com/contest/1076/problem/B
 * Submit Date : 2025-09-11
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  ll res(0);
  if (n % 2) {
    for (ll p = 3; p * p <= n; p += 2) {
      if (n % p == 0) {
        n -= p;
        res = 1;
        break;
      }
    }
    if (!res) {
      res = 1;
      n = 0;
    }
  }

  if (n > 0) {
    res += n / 2;
  }
  printf("%lld\n", res);

  return 0;
}
