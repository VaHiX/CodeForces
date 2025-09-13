/*
 * Problem URL : https://codeforces.com/problemset/problem/1692/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    printf("%d\n", (b > a) + (c > a) + (d > a));
  }
}
