/*
 * Problem URL : https://codeforces.com/problemset/problem/2024/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long res(0);
    if (a >= b) {
      res = a;
    } else if (2 * a >= b) {
      res = 2 * a - b;
    }
    printf("%ld\n", res);
  }
}
