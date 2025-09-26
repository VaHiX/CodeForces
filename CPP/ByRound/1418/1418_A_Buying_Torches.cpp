/*
 * Problem URL : https://codeforces.com/contest/1418/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1418/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x, y, k;
    scanf("%lld %lld %lld", &x, &y, &k);
    ll a = (k * (y + 1) - 1 + (x - 2)) / (x - 1);
    printf("%lld\n", a + k);
  }

  return 0;
}
