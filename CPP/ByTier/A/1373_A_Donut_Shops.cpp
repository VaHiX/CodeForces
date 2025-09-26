/*
 * Problem URL : https://codeforces.com/contest/1373/problem/A
 * Submit Date : 2025-08-26
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld %lld\n", (a < c ? 1LL : -1LL), (c < b * a ? b : -1LL));
  }

  return 0;
}
