/*
 * Problem URL : https://codeforces.com/contest/1486/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1486/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll carry(0);
    bool res(true);
    for (ll p = 0; p < n; p++) {
      ll h;
      scanf("%lld", &h);
      h += carry;
      if (h < p) {
        res = false;
      }
      carry = h - p;
    }
    puts(res ? "YES" : "NO");
  }
}
