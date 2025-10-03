/*
 * Problem URL : https://codeforces.com/contest/1426/problem/B
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    bool possible(false);
    for (long p = 0; p < n; p++) {
      long w, x, y, z;
      scanf("%ld%ld%ld%ld", &w, &x, &y, &z);
      if (x == y) {
        possible = true;
      }
    }

    if (m % 2) {
      possible = false;
    }
    puts(possible ? "YES" : "NO");
  }

  return 0;
}
