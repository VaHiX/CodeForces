/*
 * Problem URL : https://codeforces.com/problemset/problem/2043/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll nc(1);
    while (n >= 4) {
      nc *= 2;
      n /= 4;
    }
    printf("%lld\n", nc);
  }
}
