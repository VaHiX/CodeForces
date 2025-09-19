/*
 * Problem URL : https://codeforces.com/problemset/problem/1358/A
 * Submit Date : 2025-08-16
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long res = (n * m + 1) / 2;
    printf("%ld\n", res);
  }

  return 0;
}
