/*
 * Problem URL : https://codeforces.com/contest/1068/problem/A
 * Submit Date : 2025-08-30
 */

/*
 * Problem URL : https://codeforces.com/contest/1068/problem/A
 * Submit Date : 2025-08-28
 */



#include <cstdio>
typedef long long ll;

int main() {

  ll n, m, k, l;
  scanf("%lld %lld %lld %lld", &n, &m, &k, &l);
  ll x = (k + l + m - 1) / m;
  printf("%lld\n", (m * x <= n) ? x : -1);

  return 0;
}
