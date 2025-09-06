/*
 * Problem URL : https://codeforces.com/problemset/problem/1178/C
 * Submit Date : 2025-08-20
 */

#include <cstdio>
typedef long long ll;

int main() {

  const ll MOD = 998244353;
  ll w, h;
  scanf("%lld %lld", &w, &h);
  ll cnt(1);
  for (ll p = 0; p < w + h; p++) {
    cnt *= 2;
    cnt %= MOD;
  }
  printf("%lld\n", cnt);

  return 0;
}
