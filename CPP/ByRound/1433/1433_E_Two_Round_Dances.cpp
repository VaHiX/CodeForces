/*
 * Problem URL : https://codeforces.com/contest/1433/problem/E
 * Submit Date : 2025-09-10
 */

#include <cstdio>
typedef long long ll;

ll fact(ll x) {
  ll res(1);
  for (long p = 1; p <= x; p++) {
    res *= p;
  }
  return res;
}

int main() {

  ll n;
  scanf("%lld", &n);
  ll ans = fact(n) / (n / 2) / (n / 2) / 2;
  printf("%lld\n", ans);

  return 0;
}
