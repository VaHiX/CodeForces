/*
 * Problem URL : https://codeforces.com/contest/1700/problem/A
 * Submit Date : 2025-08-31
 */

#include <stdio.h>
int main() {
  long long t, n, m;
  for (scanf("%lld", &t); t; --t)
    scanf("%lld%lld", &n, &m), printf("%lld\n", m * (n * n + n + m - 1) / 2);
}