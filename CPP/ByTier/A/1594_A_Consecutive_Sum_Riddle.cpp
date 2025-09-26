/*
 * Problem URL : https://codeforces.com/problemset/problem/1594/A
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
    printf("%lld %lld\n", -(n - 1), n);
  }
}
