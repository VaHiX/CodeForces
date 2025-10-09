/*
 * Problem URL : https://codeforces.com/problemset/problem/1807/B
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long evens(0), odds(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) {
        odds += x;
      } else {
        evens += x;
      }
    }

    puts(evens > odds ? "YES" : "NO");
  }
}
