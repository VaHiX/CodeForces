/*
 * Problem URL : https://codeforces.com/problemset/problem/2024/B
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    sort(v.begin(), v.end());
    ll cnt(0), prev(0);
    for (ll p = 0; p < n; p++) {
      ll diff = v[p] - prev;
      prev = v[p];
      ll num = diff * (n - p);
      if (k <= num) {
        cnt += k;
        break;
      } else {
        cnt += num + 1;
        k -= num;
      }
    }

    printf("%lld\n", cnt);
  }
}
