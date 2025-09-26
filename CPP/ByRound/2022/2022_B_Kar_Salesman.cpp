/*
 * Problem URL : https://codeforces.com/problemset/problem/2022/B
 * Submit Date : 2025-08-10
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    ll sa(0), mxa(0);
    for (ll p = 0; p < n; p++) {
      ll a;
      scanf("%lld", &a);
      sa += a;
      mxa = (mxa > a ? mxa : a);
    }

    ll res((sa + x - 1) / x);
    res = (res > mxa ? res : mxa);
    printf("%lld\n", res);
  }
}
