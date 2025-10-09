/*
 * Problem URL : https://codeforces.com/problemset/problem/1828/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 1; p <= n; p++) {
      printf("%ld ", 2 * p);
    }
    puts("");
  }
}
