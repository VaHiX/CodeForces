/*
 * Problem URL : https://codeforces.com/problemset/problem/1984/C1
 * Submit Date : 2025-08-12
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll c(0), mn(0), mx(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      mn += x;
      mx += x;
      if (mn + mx < 0) {
        mx = -mn;
      }
    }

    printf("%lld\n", mx);
  }
}
