/*
 * Problem URL : https://codeforces.com/problemset/problem/2004/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a, b;
    for (long p = 0; p < n; p++) {
      b = a;
      scanf("%ld", &a);
    }
    puts((n == 2 && (b - a > 1 || b - a < -1)) ? "YES" : "NO");
  }
}
