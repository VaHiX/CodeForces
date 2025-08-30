/*
 * Problem URL : https://codeforces.com/problemset/problem/2078/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long sum(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      sum += x;
    }
    puts(sum == n * x ? "YES" : "NO");
  }
}
