/*
 * Problem URL : https://codeforces.com/contest/1486/problem/B
 * Submit Date : 2025-09-10
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> x(n), y(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld %lld", &x[p], &y[p]);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    ll dx = x[n / 2] - x[(n - 1) / 2] + 1;
    ll dy = y[n / 2] - y[(n - 1) / 2] + 1;
    ll ans = dx * dy;
    printf("%lld\n", ans);
  }
}
