/*
 * Problem URL : https://codeforces.com/problemset/problem/1767/A
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long xa, ya, xb, yb, xc, yc;
    scanf("%ld %ld", &xa, &ya);
    scanf("%ld %ld", &xb, &yb);
    scanf("%ld %ld", &xc, &yc);
    puts(((xa == xb || xa == xc || xb == xc) &&
          (ya == yb || ya == yc || yb == yc))
             ? "NO"
             : "YES");
  }
}
