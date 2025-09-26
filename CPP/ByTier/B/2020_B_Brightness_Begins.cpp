/*
 * Problem URL : https://codeforces.com/problemset/problem/2020/B
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll k;
    scanf("%lld", &k);
    printf("%lld\n", k + (ll)(sqrtl(k) + 0.5));
  }
}
