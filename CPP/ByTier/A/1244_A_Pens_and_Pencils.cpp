/*
 * Problem URL : https://codeforces.com/problemset/problem/1244/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d, k;
    scanf("%ld %ld %ld %ld %ld", &a, &b, &c, &d, &k);
    long x = (a + c - 1) / c;
    long y = (b + d - 1) / d;
    if (x + y > k) {
      puts("-1");
      continue;
    }
    printf("%ld %ld\n", x, y);
  }

  return 0;
}
