/*
 * Problem URL : https://codeforces.com/problemset/problem/1822/B
 * Submit Date : 2025-08-18
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.begin(), a.end());
    ll u = a[0] * a[1];
    ll v = a[n - 2] * a[n - 1];
    printf("%lld\n", u > v ? u : v);
  }
}
