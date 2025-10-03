/*
 * Problem URL : https://codeforces.com/contest/1425/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1425/A
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
    ll res(0);
    while (n > 0) {
      if (n % 4 == 2 || n == 4) {
        res += n / 2;
        n /= 2;
      } else {
        ++res;
        --n;
      }

      if (n <= 0) {
        break;
      }

      if (n % 4 == 2 || n == 4) {
        n /= 2;
      } else {
        --n;
      }
    }

    printf("%lld\n", res);
  }

  return 0;
}
