/*
 * Problem URL : https://codeforces.com/contest/952/problem/C
 * Submit Date : 2025-09-12
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long prev(0), cur(0);
  bool possible(true);
  for (long p = 0; p < n; p++) {
    long cur;
    scanf("%ld", &cur);
    if (p > 0 && ((cur - prev > 1) || (prev - cur > 1))) {
      possible = false;
      break;
    }
    prev = cur;
  }

  puts(possible ? "YES" : "NO");

  return 0;
}
