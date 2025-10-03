/*
 * Problem URL : https://codeforces.com/problemset/problem/1646/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, s;
    scanf("%lld %lld", &n, &s);
    printf("%lld\n", s / (n * n));
  }
}
