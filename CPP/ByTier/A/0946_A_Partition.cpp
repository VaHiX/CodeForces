/*
 * Problem URL : https://codeforces.com/contest/946/problem/A
 * Submit Date : 2025-08-31
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long res(0);
  while (n--) {
    long x;
    scanf("%ld", &x);
    if (x > 0) {
      res += x;
    } else {
      res -= x;
    }
  }

  printf("%ld\n", res);

  return 0;
}
