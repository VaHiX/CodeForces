/*
 * Problem URL : https://codeforces.com/problemset/problem/1562/A
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long res = (r >= 2 * l) ? (r - 1) / 2 : (r - l);
    printf("%ld\n", res);
  }
}
