/*
 * Problem URL : https://codeforces.com/problemset/problem/1810/A
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool res(false);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= p) {
        res = true;
      }
    }

    puts(res ? "YES" : "NO");
  }
}
