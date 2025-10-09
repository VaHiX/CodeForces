/*
 * Problem URL : https://codeforces.com/contest/1455/problem/C
 * Submit Date : 2025-08-26
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    printf("%ld %ld\n", x - 1, y);
  }
}
