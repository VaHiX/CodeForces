/*
 * Problem URL : https://codeforces.com/problemset/problem/1651/A
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
    ll res(1);
    while (n--) {
      res *= 2;
    }
    printf("%lld\n", res - 1);
  }
}
