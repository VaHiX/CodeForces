/*
 * Problem URL : https://codeforces.com/contest/1575/problem/K
 * Submit Date : 2025-09-08
 */

#include <cstdio>
const long long MOD = 1000000007;
long long POWER(long long a, long long b, long long c) {
  long long r = 1 % c;
  for (; b; b >>= 1) {
    if (b & 1)
      r = r * a % c;
    a = a * a % c;
  }
  return r;
}
int main() {
  int n, m, k, r, c;
  scanf("%d%d%d%d%d", &n, &m, &k, &r, &c);
  int ax, ay, bx, by;
  scanf("%d%d%d%d", &ax, &ay, &bx, &by);
  if (ax == bx && ay == by)
    printf("%lld\n", POWER(k, (long long)n * m % (MOD - 1), MOD));
  else
    printf("%lld\n",
           POWER(k, ((long long)n * m - (long long)r * c) % (MOD - 1), MOD));
  return 0;
}
