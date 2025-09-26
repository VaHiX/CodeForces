/*
 * Problem URL : https://codeforces.com/problemset/problem/1539/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, x, t;
    scanf("%lld %lld %lld", &n, &x, &t);
    ll a = (t / x);
    a = (a < n) ? a : n;
    ll res = n * a - a * (a + 1) / 2;
    printf("%lld\n", res);
  }
}
