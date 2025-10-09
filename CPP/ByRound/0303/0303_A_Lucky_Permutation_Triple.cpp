/*
 * Problem URL : https://codeforces.com/contest/303/problem/A
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld\n", &n);

  if (n % 2) {
    for (long p = 0; p < n; p++) {
      printf("%ld ", p);
    };
    puts("");
    for (long p = 0; p < n; p++) {
      printf("%ld ", p);
    };
    puts("");
    for (long p = 0; p < n; p++) {
      printf("%ld ", (2 * p) % n);
    };
    puts("");
  } else {
    puts("-1");
  }

  return 0;
}
