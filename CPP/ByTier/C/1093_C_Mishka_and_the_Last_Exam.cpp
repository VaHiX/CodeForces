/*
 * Problem URL : https://codeforces.com/contest/1093/problem/C
 * Submit Date : 2025-09-09
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n, 0);
  ll left(0), right(1e18);
  for (ll p = 0; 2 * p < n; p++) {
    ll b;
    scanf("%lld", &b);
    a[p] = (b - left <= right) ? left : (b - right);
    a[n - 1 - p] = b - a[p];
    left = a[p];
    right = a[n - 1 - p];
  }

  for (ll p = 0; p < n; p++) {
    printf("%lld ", a[p]);
  }

  return 0;
}
