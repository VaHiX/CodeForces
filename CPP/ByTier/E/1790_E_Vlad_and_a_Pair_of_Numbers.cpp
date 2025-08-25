/*
 * Problem URL : https://codeforces.com/problemset/problem/1790/E
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    if (x % 2) {
      puts("-1");
      continue;
    }
    long a(x / 2), b(x + x / 2);
    if ((a ^ b) != x) {
      puts("-1");
    } else {
      printf("%ld %ld\n", a, b);
    }
  }
}
