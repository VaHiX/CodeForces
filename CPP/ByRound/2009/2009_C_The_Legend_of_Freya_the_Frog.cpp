/*
 * Problem URL : https://codeforces.com/problemset/problem/2009/C
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, k;
    scanf("%ld %ld %ld", &x, &y, &k);
    x = (x + k - 1) / k;
    y = (y + k - 1) / k;
    printf("%ld\n", 2 * (x > y ? x : y) - (x > y));
  }
}
