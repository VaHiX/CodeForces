/*
 * Problem URL : https://codeforces.com/problemset/problem/1855/B
 * Submit Date : 2025-08-15
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1855/B
 * Submit Date : 2025-08-15
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cnt(1);
    for (ll p = 2; n % p == 0 && p <= n; p++) {
      ++cnt;
    }
    printf("%lld\n", cnt);
  }
}
