/*
 * Problem URL : https://codeforces.com/problemset/problem/1036/A
 * Submit Date : 2025-08-19
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll n, k;
  scanf("%lld %lld", &n, &k);
  printf("%lld\n", (k + n - 1) / n);

  return 0;
}
