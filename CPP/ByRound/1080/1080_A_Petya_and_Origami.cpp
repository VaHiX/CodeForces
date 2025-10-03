/*
 * Problem URL : https://codeforces.com/contest/1080/problem/A
 * Submit Date : 2025-08-30
 */

/*
 * Problem URL : https://codeforces.com/contest/1080/problem/A
 * Submit Date : 2025-08-28
 */

#include <cstdio>
typedef long long ll;

int main() {

  ll n, k;
  scanf("%lld %lld", &n, &k);
  ll total(0);
  total += (2 * n + k - 1) / k;
  total += (5 * n + k - 1) / k;
  total += (8 * n + k - 1) / k;
  printf("%lld\n", total);

  return 0;
}
