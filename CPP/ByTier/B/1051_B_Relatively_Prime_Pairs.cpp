/*
 * Problem URL : https://codeforces.com/problemset/problem/1051/B
 * Submit Date : 2025-08-13
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll l, r;
  scanf("%lld %lld", &l, &r);
  puts("YES");
  for (ll p = l; p <= r; p += 2) {
    printf("%lld %lld\n", p, p + 1);
  }

  return 0;
}
