/*
 * Problem URL : https://codeforces.com/problemset/problem/2108/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%lld\n", 1 + (long long)n * n / 4);
  }
}
