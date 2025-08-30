/*
 * Problem URL : https://codeforces.com/problemset/problem/1902/B
 * Submit Date : 2025-08-14
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, P, l, s;
    scanf("%lld %lld %lld %lld", &n, &P, &l, &s);
    ll ns = (n + 6) / 7;
    ll a = (P + l + 2 * s - 1) / (l + 2 * s);
    ll b = (P - s * ns + l - 1) / l;
    ll res = n - (a > b ? a : b);
    printf("%lld\n", res);
  }
}
