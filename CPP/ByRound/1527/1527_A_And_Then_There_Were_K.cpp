/*
 * Problem URL : https://codeforces.com/problemset/problem/1527/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x(1);
    while (2 * x <= n) {
      x *= 2;
    }
    --x;
    printf("%ld\n", x);
  }
}
