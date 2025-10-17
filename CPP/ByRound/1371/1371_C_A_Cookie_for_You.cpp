/*
 * Problem URL : https://codeforces.com/contest/1371/problem/C
 * Submit Date : 2025-09-11
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, n, m;
    scanf("%lld %lld %lld %lld", &a, &b, &n, &m);
    ll least = (a < b) ? a : b;
    puts(((m + n <= a + b) && (m <= least)) ? "Yes" : "No");
  }

  return 0;
}
