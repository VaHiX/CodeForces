/*
 * Problem URL : https://codeforces.com/problemset/problem/1007/A
 * Submit Date : 2025-08-18
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end());
  ll left(0), right(0), cnt(0);
  while (right < n && a[left] == a[right]) {
    ++right;
  }
  while (right < n) {
    if (a[left] < a[right]) {
      ++cnt;
      ++left;
    }
    ++right;
  }

  printf("%lld\n", cnt);

  return 0;
}
