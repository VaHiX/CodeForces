/*
 * Problem URL : https://codeforces.com/problemset/problem/1914/E2
 * Submit Date : 2025-08-12
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
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &b[p]);
    }

    std::vector<std::pair<ll, ll>> s(n);
    for (long p = 0; p < n; p++) {
      s[p].first = a[p] + b[p];
      s[p].second = p;
    }
    sort(s.rbegin(), s.rend());

    ll res(0);
    for (long p = 0; p < n; p++) {
      long idx = s[p].second;
      if (p % 2) {
        res -= (b[idx] - 1);
      } else {
        res += a[idx] - 1;
      }
    }

    printf("%lld\n", res);
  }
}
