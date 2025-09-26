/*
 * Problem URL : https://codeforces.com/problemset/problem/1793/A
 * Submit Date : 2025-08-20
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll cfa = m * a * (n / (m + 1));
    ll cfb = (m + 1) * b * (n / (m + 1));
    ll cf = (cfa < cfb) ? cfa : cfb;
    ll cs = (a < b ? a : b) * (n % (m + 1));
    ll cost = cf + cs;
    printf("%lld\n", cost);
  }
}
