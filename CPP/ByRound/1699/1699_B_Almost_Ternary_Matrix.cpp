/*
 * Problem URL : https://codeforces.com/contest/1699/problem/B
 * Submit Date : 2025-09-07
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    for (long row = 1; row <= n; row++) {
      for (long col = 1; col <= m; col++) {
        printf("%d ", ((row % 4 <= 1) != (col % 4 <= 1)));
      }
      puts("");
    }
  }
}
