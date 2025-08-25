/*
 * Problem URL : https://codeforces.com/problemset/problem/1475/A
 * Submit Date : 2025-08-13
 */

#include <cstdio>
typedef long long ll;

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    while (n % 2 == 0) {
      n /= 2;
    }
    puts(n > 1 ? "YES" : "NO");
  }
}
