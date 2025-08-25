/*
 * Problem URL : https://codeforces.com/problemset/problem/1077/C
 * Submit Date : 2025-08-20
 */

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  std::vector<std::pair<ll, ll>> a(n);
  ll sum(0);

  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p].first);
    a[p].second = p;
    sum += a[p].first;
  }
  sort(a.begin(), a.end());

  std::vector<ll> ids;
  for (ll p = 0; p < n; p++) {
    if ((p + 1 < n) && (sum - a[p].first == 2 * a[n - 1].first)) {
      ids.push_back(1 + a[p].second);
    } else if ((p == n - 1) && (sum - a[n - 1].first == 2 * a[n - 2].first)) {
      ids.push_back(1 + a[p].second);
    }
  }
  printf("%ld\n", ids.size());
  for (ll p = 0; p < ids.size(); p++) {
    printf("%lld ", ids[p]);
  }
  puts("");

  return 0;
}
