/*
 * Problem URL : https://codeforces.com/contest/1151/problem/D
 * Submit Date : 2025-09-11
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  std::vector<std::pair<ll, std::pair<ll, ll>>> v(n);
  for (ll p = 0; p < n; p++) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    v[p].first = b - a;
    v[p].second = std::make_pair(a, b);
  }

  sort(v.begin(), v.end());
  ll res(0);
  for (ll p = 0; p < n; p++) {
    res += p * (v[p].second.first) + (n - 1 - p) * v[p].second.second;
  }
  printf("%lld\n", res);

  return 0;
}
