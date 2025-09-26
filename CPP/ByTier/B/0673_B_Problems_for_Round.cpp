/*
 * Problem URL : https://codeforces.com/problemset/problem/673/B
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long n, m;
  scanf("%ld %ld\n", &n, &m);
  long min(n), max(1);
  while (m--) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    if (y < x) {
      long temp = x;
      x = y;
      y = temp;
    }
    if (max < x) {
      max = x;
    }
    if (y < min) {
      min = y;
    }
  }

  printf("%ld\n", (max < min) ? (min - max) : 0);

  return 0;
}
