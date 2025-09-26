/*
 * Problem URL : https://codeforces.com/problemset/problem/1584/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll u, v;
    scanf("%lld %lld", &u, &v);
    printf("%lld %lld\n", u * u, -v * v);
  }
}
