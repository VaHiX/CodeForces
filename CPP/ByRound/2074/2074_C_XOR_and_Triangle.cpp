/*
 * Problem URL : https://codeforces.com/problemset/problem/2074/C
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    long y = (x & -x) | (~x & -~x);
    printf("%ld\n", (y < x ? y : -1));
  }
}
