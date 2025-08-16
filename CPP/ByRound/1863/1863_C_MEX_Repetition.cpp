/*
 * Problem URL : https://codeforces.com/problemset/problem/1863/C
 * Submit Date : 2025-08-15
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
    std::vector<ll> a(n + 1);
    a[n] = n * (n + 1) / 2;
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      a[n] -= a[p];
    }
    k %= (n + 1);
    for (ll p = 0; p < n; p++) {
      printf("%lld ", a[(p - k + n + 1) % (n + 1)]);
    }
    puts("");
  }
}
