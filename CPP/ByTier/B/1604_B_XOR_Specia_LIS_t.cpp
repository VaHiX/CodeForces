/*
 * Problem URL : https://codeforces.com/contest/1604/problem/B
 * Submit Date : 2025-08-26
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev;
    scanf("%ld", &prev);
    bool inc(true);
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= prev) {
        inc = false;
      }
      prev = x;
    }

    puts((n % 2) && inc ? "NO" : "YES");
  }
}
