/*
 * Problem URL : https://codeforces.com/problemset/problem/1436/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long s(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x;
    }
    puts(s == m ? "YES" : "NO");
  }

  return 0;
}
