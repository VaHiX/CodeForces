/*
 * Problem URL : https://codeforces.com/problemset/problem/1921/D
 * Submit Date : 2025-08-12
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(m);
    for (ll p = 0; p < m; p++) {
      scanf("%lld", &b[p]);
    }
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());

    ll diff(0), left(0), right(n - 1), idxL(0), idxR(m - 1);
    while (left <= right) {
      long curA = a[left] - b[idxL];
      curA = (curA > 0 ? curA : -curA);
      long curB = a[right] - b[idxR];
      curB = (curB > 0 ? curB : -curB);
      if (curA > curB) {
        diff += curA;
        ++left;
        ++idxL;
      } else {
        diff += curB;
        --right;
        --idxR;
      }
    }

    printf("%lld\n", diff);
  }
}
