/*
 * Problem URL : https://codeforces.com/problemset/problem/1708/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s;
    scanf("%ld", &s);
    bool possible(true);
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % s) {
        possible = false;
      }
    }

    puts(possible ? "YES" : "NO");
  }
}
