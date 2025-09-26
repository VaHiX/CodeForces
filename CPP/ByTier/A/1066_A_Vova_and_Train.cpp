/*
 * Problem URL : https://codeforces.com/contest/1066/problem/A
 * Submit Date : 2025-08-30
 */

/*
 * Problem URL : https://codeforces.com/contest/1066/problem/A
 * Submit Date : 2025-08-28
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll L, v, l, r;
    scanf("%lld %lld %lld %lld\n", &L, &v, &l, &r);
    printf("%lld\n", (L / v) - (r / v) + (l - 1) / v);
  }
  return 0;
}
