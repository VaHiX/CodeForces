/*
 * Problem URL : https://codeforces.com/problemset/problem/1270/A
 * Submit Date : 2025-08-13
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    bool first(0);
    for (long p = 0; p < a; p++) {
      long x;
      scanf("%ld", &x);
      first = first | (x == n);
    }
    for (long p = 0; p < b; p++) {
      long x;
      scanf("%ld", &x);
    }
    puts(first ? "YES" : "NO");
  }

  return 0;
}
