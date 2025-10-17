/*
 * Problem URL : https://codeforces.com/problemset/problem/1470/A
 * Submit Date : 2025-08-16
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
    std::vector<ll> kv(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &kv[p]);
      --kv[p];
    }
    sort(kv.rbegin(), kv.rend());
    std::vector<ll> c(m);
    for (ll p = 0; p < m; p++) {
      scanf("%lld", &c[p]);
    }
    ll res(0);
    for (ll p = 0; p < n; p++) {
      ll idx = (p < kv[p]) ? p : kv[p];
      res += c[idx];
    }

    printf("%lld\n", res);
  }
}
