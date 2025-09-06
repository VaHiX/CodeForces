/*
 * Problem URL : https://codeforces.com/problemset/problem/2004/C
 * Submit Date : 2025-08-10
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
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.rbegin(), a.rend());
    ll A(0), B(0);
    for (ll p = 0; p < n; p++) {
      if (p % 2) {
        ll diff = (a[p - 1] - a[p]);
        diff = (diff < k ? diff : k);
        k -= diff;
        B += a[p] + diff;
      } else {
        A += a[p];
      }
    }

    printf("%lld\n", A - B);
  }
}
