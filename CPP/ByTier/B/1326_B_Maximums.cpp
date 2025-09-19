/*
 * Problem URL : https://codeforces.com/problemset/problem/1326/B
 * Submit Date : 2025-08-22
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  ll mx(0);
  for (ll p = 0; p < n; p++) {
    ll b;
    scanf("%lld", &b);
    ll a = b + mx;
    printf("%lld ", a);
    mx = (mx > a) ? mx : a;
  }

  puts("");

  return 0;
}
