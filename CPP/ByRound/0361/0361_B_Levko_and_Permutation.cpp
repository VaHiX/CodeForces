/*
 * Problem URL : https://codeforces.com/contest/361/problem/B
 * Submit Date : 2025-09-08
 */

#include <cstdio>

int main() {

  long n(0), k(0);
  scanf("%ld %ld", &n, &k);

  if (k >= n) {
    puts("-1");
  } else {
    for (long p = 1; p <= n - k - 1; p++) {
      printf("%ld ", p + 1);
    }
    printf("1 ");
    for (long p = n - k + 1; p <= n; p++) {
      printf("%ld ", p);
    }
    puts("");
  }

  return 0;
}
