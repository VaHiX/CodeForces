/*
 * Problem URL : https://codeforces.com/problemset/problem/1971/E
 * Submit Date : 2025-08-12
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k, q;
    scanf("%lld %lld %lld", &n, &k, &q);
    std::vector<ll> a(k + 1, 0), b(k + 1, 0);
    for (ll p = 1; p <= k; p++) {
      scanf("%lld", &a[p]);
    }
    for (ll p = 1; p <= k; p++) {
      scanf("%lld", &b[p]);
    }

    for (ll p = 0; p < q; p++) {
      ll d;
      scanf("%lld", &d);
      if (d == n) {
        printf("%lld ", b.back());
        continue;
      }
      ll idx = std::upper_bound(a.begin(), a.end(), d) - a.begin();
      printf("%lld ", b[idx - 1] + (b[idx] - b[idx - 1]) * (d - a[idx - 1]) /
                                       (a[idx] - a[idx - 1]));
    }
    puts("");
  }
}
