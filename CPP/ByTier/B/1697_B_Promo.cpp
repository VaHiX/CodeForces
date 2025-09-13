/*
 * Problem URL : https://codeforces.com/contest/1697/problem/B
 * Submit Date : 2025-08-30
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll n, q;
  scanf("%lld %lld", &n, &q);
  std::vector<ll> v(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &v[p]);
  }
  sort(v.begin(), v.end());
  std::vector<ll> f(n + 1, 0);
  for (ll p = 1; p <= n; p++) {
    f[p] = f[p - 1] + v[p - 1];
  }
  while (q--) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    ll res = f[n - x + y] - f[n - x];
    printf("%lld\n", res);
  }
}
