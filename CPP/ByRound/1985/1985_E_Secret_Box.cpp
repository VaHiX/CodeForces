/*
 * Problem URL : https://codeforces.com/problemset/problem/1985/E
 * Submit Date : 2025-08-12
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x, y, z, k;
    scanf("%lld %lld %lld %lld", &x, &y, &z, &k);
    ll ans = 0;
    for (ll a = 1; a <= x; a++) {
      for (ll b = 1; b <= y; b++) {
        if (k % (a * b))
          continue;
        ll c = k / (a * b);
        if (c > z)
          continue;
        ll ways = (x - a + 1) * (y - b + 1) * (z - c + 1);
        ans = (ans > ways ? ans : ways);
      }
    }

    printf("%lld\n", ans);
  }
}
