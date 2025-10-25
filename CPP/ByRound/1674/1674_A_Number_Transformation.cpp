/*
 * Problem URL : https://codeforces.com/problemset/problem/1674/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    if (y % x) {
      puts("0 0");
    } else {
      printf("1 %ld\n", y / x);
    }
  }
}
