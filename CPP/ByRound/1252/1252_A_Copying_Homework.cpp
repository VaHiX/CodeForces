/*
 * Problem URL : https://codeforces.com/contest/1252/problem/A
 * Submit Date : 2025-08-27
 */



#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    printf("%ld ", (n + 1 - x));
  }
  puts("");

  return 0;
}
