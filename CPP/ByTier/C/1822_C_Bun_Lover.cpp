/*
 * Problem URL : https://codeforces.com/problemset/problem/1822/C
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
    ll res = 1 + (n + 1) * (n + 1);
    printf("%lld\n", res);
  }
}
