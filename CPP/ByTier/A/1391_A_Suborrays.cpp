/*
 * Problem URL : https://codeforces.com/contest/1391/problem/A
 * Submit Date : 2025-08-25
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 1; p <= n; p++) {
      printf("%ld ", p);
    }
    puts("");
  }

  return 0;
}
