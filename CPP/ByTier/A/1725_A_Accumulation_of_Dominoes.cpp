/*
 * Problem URL : https://codeforces.com/problemset/problem/1725/A
 * Submit Date : 2025-08-14
 */

#include <cstdio>

int main() {

  long long n, m;
  scanf("%lld %lld", &n, &m);
  printf("%lld\n", (m > 1) ? n * (m - 1) : (n - 1));
}
