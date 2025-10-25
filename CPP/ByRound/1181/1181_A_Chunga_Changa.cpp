/*
 * Problem URL : https://codeforces.com/contest/1181/problem/A
 * Submit Date : 2025-08-27
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll x, y, z;
  scanf("%lld %lld %lld", &x, &y, &z);
  ll total = (x + y) / z;
  ll give(0);
  if (x % z + y % z >= z) {
    give = z - (((x % z) > (y % z)) ? (x % z) : (y % z));
  }
  printf("%lld %lld\n", total, give);

  return 0;
}
