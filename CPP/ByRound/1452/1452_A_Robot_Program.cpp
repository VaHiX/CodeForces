/*
 * Problem URL : https://codeforces.com/problemset/problem/1452/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long res = 2 * (x > y ? x : y) - (x != y);
    printf("%ld\n", res);
  }
}
