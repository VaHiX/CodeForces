/*
 * Problem URL : https://codeforces.com/problemset/problem/1915/E
 * Submit Date : 2025-08-12
 */

#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      if (p % 2) {
        v[p] = -v[p];
      }
    }

    ll cs(0);
    bool ans(false);
    std::set<ll> w;
    w.insert(0);
    for (ll p = 0; !ans && p < n; p++) {
      cs += v[p];
      if (w.count(cs)) {
        ans = true;
      }
      w.insert(cs);
    }

    puts(ans ? "YES" : "NO");
  }
}
