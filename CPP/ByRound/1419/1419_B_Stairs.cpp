/*
 * Problem URL : https://codeforces.com/contest/1419/problem/B
 * Submit Date : 2025-09-10
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x;
    scanf("%lld", &x);
    ll y(1), res(0);
    while (2 * x >= y * (y + 1)) {
      x -= y * (y + 1) / 2;
      y = 2 * y + 1;
      ++res;
    }

    printf("%lld\n", res);
  }

  return 0;
}
