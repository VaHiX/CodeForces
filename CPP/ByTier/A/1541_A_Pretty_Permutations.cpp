/*
 * Problem URL : https://codeforces.com/problemset/problem/1541/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long start(1);
    if (n % 2) {
      start = 4;
      printf("3 1 2 ");
    }
    for (long p = start; p < n; p += 2) {
      printf("%ld %ld ", p + 1, p);
    }
    puts("");
  }
}
