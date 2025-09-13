/*
 * Problem URL : https://codeforces.com/problemset/problem/1877/A
 * Submit Date : 2025-08-15
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cs(0);
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      cs += x;
    }
    printf("%ld\n", -cs);
  }
}
