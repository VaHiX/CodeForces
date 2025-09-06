/*
 * Problem URL : https://codeforces.com/contest/1422/problem/B
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1422/B
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<std::vector<ll>> w(n, std::vector<ll>(m, 0));
    for (ll row = 0; row < n; row++) {
      for (ll col = 0; col < m; col++) {
        scanf("%lld", &w[row][col]);
      }
    }

    ll total(0);
    for (ll row = 0; row < n; row++) {
      for (ll col = 0; col < m; col++) {
        std::vector<ll> v = {w[row][col], w[row][m - 1 - col],
                             w[n - 1 - row][m - 1 - col], w[n - 1 - row][col]};
        sort(v.begin(), v.end());
        total += std::abs(v[1] - w[row][col]);
      }
    }

    printf("%lld\n", total);
  }
}
