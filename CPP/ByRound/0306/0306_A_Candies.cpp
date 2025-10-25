/*
 * Problem URL : https://codeforces.com/contest/306/problem/A
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long n, m;
  scanf("%ld %ld", &n, &m);
  long ratio = n / m;
  long rem = n % m;
  for (long p = 0; p < m; p++) {
    printf("%ld ", ratio + (p < rem));
  }
  puts("");

  return 0;
}
