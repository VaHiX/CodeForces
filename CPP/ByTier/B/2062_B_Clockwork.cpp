/*
 * Problem URL : https://codeforces.com/problemset/problem/2062/B
 * Submit Date : 2025-08-10
 */

#include <algorithm>
#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool possible(true);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      long dist = 2 * std::max(p, n - 1 - p);
      if (x <= dist) {
        possible = false;
      }
    }

    puts(possible ? "YES" : "NO");
  }
}
