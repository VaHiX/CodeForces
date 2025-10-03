/*
 * Problem URL : https://codeforces.com/problemset/problem/1769/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long prev(-100);
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    x -= p;
    prev = (x > (prev + 1) ? x : (prev + 1));
    printf("%ld\n", prev);
  }
}
