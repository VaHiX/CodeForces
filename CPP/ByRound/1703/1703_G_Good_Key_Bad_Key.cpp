/*
 * Problem URL : https://codeforces.com/problemset/problem/1703/G
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1703/G
 * Submit Date : 2025-08-21
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> a(n, 0);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }

    ll goodsum(0), maxsum(0);
    for (ll p = 0; p <= n; p++) {
      ll badsum(0);
      for (ll u = 0; p + u < n && u < 31; u++) {
        badsum += (a[p + u] / (2 << u));
      }
      ll total = goodsum + badsum;
      maxsum = (maxsum > total ? maxsum : total);
      if (p == n) {
        continue;
      }
      goodsum += (a[p] - k);
    }

    printf("%lld\n", maxsum);
  }
}
