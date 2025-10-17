/*
 * Problem URL : https://codeforces.com/problemset/problem/1635/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0);
    while (n--) {
      long x;
      scanf("%ld", &x);
      res |= x;
    }

    printf("%ld\n", res);
  }
}
