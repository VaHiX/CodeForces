/*
 * Problem URL : https://codeforces.com/problemset/problem/1987/B
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
    ll prev(0), total(0), mxd(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if (x >= prev) {
        prev = x;
      } else {
        ll diff = prev - x;
        total += diff;
        mxd = (mxd > diff ? mxd : diff);
      }
    }

    printf("%lld\n", total + mxd);
  }
}
