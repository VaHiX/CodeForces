/*
 * Problem URL : https://codeforces.com/contest/1296/problem/D
 * Submit Date : 2025-09-11
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll n, a, b, k;
  scanf("%lld %lld %lld %lld", &n, &a, &b, &k);
  std::vector<ll> f(n);
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    const ll s = a + b;
    x = (x % s == 0) ? s : (x % s);
    x = (x > a) ? (x - a) : 0;
    f[p] = (x + a - 1) / a;
  }

  sort(f.begin(), f.end());
  ll cnt(0);
  for (ll p = 0; k && p < n; p++) {
    cnt += (k >= f[p]);
    k -= f[p];
  }

  printf("%lld\n", cnt);

  return 0;
}
