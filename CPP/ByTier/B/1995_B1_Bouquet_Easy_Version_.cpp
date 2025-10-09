/*
 * Problem URL : https://codeforces.com/problemset/problem/1995/B1
 * Submit Date : 2025-08-11
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
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    sort(v.begin(), v.end());
    ll left(0), cur(0), mx(0);
    for (ll p = 0; p < n; p++) {
      cur += v[p];
      while (v[left] + 1 < v[p]) {
        cur -= v[left++];
      }
      while (cur > m) {
        cur -= v[left++];
      }
      mx = (mx > cur ? mx : cur);
    }

    printf("%lld\n", mx);
  }
}
