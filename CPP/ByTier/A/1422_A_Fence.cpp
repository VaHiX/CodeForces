/*
 * Problem URL : https://codeforces.com/problemset/problem/1422/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld\n", a + b + c - 2);
  }

  return 0;
}
