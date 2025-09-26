/*
 * Problem URL : https://codeforces.com/problemset/problem/1582/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long fa, fb, fc;
    scanf("%ld %ld %ld", &fa, &fb, &fc);
    printf("%ld\n", (fa + fc) % 2);
  }
}
