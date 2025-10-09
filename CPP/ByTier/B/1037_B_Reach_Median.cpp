/*
 * Problem URL : https://codeforces.com/problemset/problem/1037/B
 * Submit Date : 2025-08-19
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, s;
  scanf("%lld %lld", &n, &s);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end());
  ll cnt(0);
  for (ll p = 0; p < n; p++) {
    if ((2 * p + 1 <= n) && (a[p] > s)) {
      cnt += (a[p] - s);
    } else if ((2 * p + 1 >= n) && (a[p] < s)) {
      cnt += (s - a[p]);
    }
  }

  printf("%lld\n", cnt);

  return 0;
}
