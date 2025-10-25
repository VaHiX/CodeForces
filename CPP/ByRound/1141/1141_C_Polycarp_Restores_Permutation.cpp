/*
 * Problem URL : https://codeforces.com/contest/1141/problem/C
 * Submit Date : 2025-09-08
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n, 0);
  ll x(0);
  for (ll p = 1; p < n; p++) {
    scanf("%lld", &a[p]);
    a[p] += a[p - 1];
    x = (x < a[p]) ? x : a[p];
  }
  for (ll p = 0; p < n; p++) {
    a[p] -= x - 1;
  }
  std::vector<bool> b(n + 1, false);
  bool possible(true);
  for (ll p = 0; p < n; p++) {
    if (a[p] > n || b[a[p]]) {
      possible = false;
      break;
    }
    b[a[p]] = true;
  }

  if (possible) {
    for (long p = 0; p < n; p++) {
      printf("%lld ", a[p]);
    };
    puts("");
  } else {
    puts("-1");
  }

  return 0;
}
