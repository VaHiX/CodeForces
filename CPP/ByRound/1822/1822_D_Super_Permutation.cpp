/*
 * Problem URL : https://codeforces.com/problemset/problem/1822/D
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 1) {
      puts("1");
      continue;
    }
    if (n % 2) {
      puts("-1");
      continue;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", p % 2 ? p : (n - p));
    }
    puts("");
  }
}
