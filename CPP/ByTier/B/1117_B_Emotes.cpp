/*
 * Problem URL : https://codeforces.com/contest/1117/problem/B
 * Submit Date : 2025-08-28
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  std::vector<ll> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.rbegin(), a.rend());
  ll total = (m / (k + 1)) * (k * a[0] + a[1]) + (m % (k + 1)) * a[0];
  printf("%lld\n", total);

  return 0;
}
