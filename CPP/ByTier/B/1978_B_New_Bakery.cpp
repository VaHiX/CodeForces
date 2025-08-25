/*
 * Problem URL : https://codeforces.com/problemset/problem/1978/B
 * Submit Date : 2025-08-12
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, a, b;
    scanf("%lld %lld %lld", &n, &a, &b);
    ll k = b - a;
    k = (k > 0 ? k : 0);
    k = (k < n ? k : n);
    ll total = b * k - k * (k - 1) / 2 + (n - k) * a;
    printf("%lld\n", total);
  }
}
