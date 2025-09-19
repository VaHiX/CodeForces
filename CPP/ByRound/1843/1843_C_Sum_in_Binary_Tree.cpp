/*
 * Problem URL : https://codeforces.com/problemset/problem/1843/C
 * Submit Date : 2025-08-18
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(0);
    while (n) {
      res += n;
      n /= 2;
    }
    printf("%lld\n", res);
  }
}
