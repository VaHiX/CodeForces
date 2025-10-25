/*
 * Problem URL : https://codeforces.com/contest/1023/problem/B
 * Submit Date : 2025-08-30
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll n, k;
  scanf("%lld %lld", &n, &k);
  ll a = k - ((k - 1 < n) ? (k - 1) : n);
  ll b = ((k - 1) / 2 < n) ? ((k - 1) / 2) : n;
  ll ans = b - a + 1;
  printf("%lld\n", ans > 0 ? ans : 0);

  return 0;
}
