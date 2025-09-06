/*
 * Problem URL : https://codeforces.com/contest/1077/problem/A
 * Submit Date : 2025-08-30
 */

/*
 * Problem URL : https://codeforces.com/contest/1077/problem/A
 * Submit Date : 2025-08-28
 */



#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b, k;
    scanf("%lld %lld %lld", &a, &b, &k);
    ll res = (a - b) * (k / 2) + a * (k % 2);
    printf("%lld\n", res);
  }

  return 0;
}
