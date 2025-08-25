/*
 * Problem URL : https://codeforces.com/problemset/problem/1657/A
 * Submit Date : 2025-08-22
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long ss = x * x + y * y;
    long z(0);
    while (z * z < ss) {
      ++z;
    }
    printf("%d\n", (x > 0 || y > 0) + (z * z > ss));
  }
}
