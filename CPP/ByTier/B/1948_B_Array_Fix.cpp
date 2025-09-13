/*
 * Problem URL : https://codeforces.com/problemset/problem/1948/B
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(-1);
    bool res(true);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      int d(x / 10), m(x % 10);
      if (prev <= d && d <= m) {
        prev = m;
      } else if (prev <= x) {
        prev = x;
      } else {
        res = false;
      }
    }

    puts(res ? "YES" : "NO");
  }
}
