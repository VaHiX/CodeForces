/*
 * Problem URL : https://codeforces.com/problemset/problem/2035/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, m, r, c;
    scanf("%lld %lld %lld %lld", &n, &m, &r, &c);
    ll res = (n - r) * m + (m - c) * 1 + (n - r) * (m - 1) * 1;
    printf("%lld\n", res);
  }
}
