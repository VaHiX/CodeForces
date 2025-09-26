/*
 * Problem URL : https://codeforces.com/problemset/problem/1743/B
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("1 ");
    for (long p = n; p > 1; p--) {
      printf("%ld ", p);
    }
    puts("");
  }
}
