/*
 * Problem URL : https://codeforces.com/contest/1487/problem/D
 * Submit Date : 2025-09-10
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cnt(0);
    for (long p = 3; p < n; p += 2) {
      long tst = (p * p + 1) / 2;
      if (tst <= n) {
        ++cnt;
      } else {
        break;
      }
    }

    printf("%lld\n", cnt);
  }
}
