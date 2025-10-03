/*
 * Problem URL : https://codeforces.com/problemset/problem/1443/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 4 * n; p > 2 * n; p -= 2) {
      printf("%ld ", p);
    }
    puts("");
  }

  return 0;
}
