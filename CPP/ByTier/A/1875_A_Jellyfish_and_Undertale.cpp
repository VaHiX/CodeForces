/*
 * Problem URL : https://codeforces.com/problemset/problem/1875/A
 * Submit Date : 2025-08-15
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, n;
    scanf("%lld %lld %lld", &a, &b, &n);
    ll res(b);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      res += (x < (a - 1)) ? x : (a - 1);
    }

    printf("%lld\n", res);
  }
}
