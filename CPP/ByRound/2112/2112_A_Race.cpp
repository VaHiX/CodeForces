/*
 * Problem URL : https://codeforces.com/problemset/problem/2112/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, x, y;
    scanf("%ld %ld %ld", &a, &x, &y);
    if (x > y) {
      long u = x;
      x = y;
      y = u;
    }
    puts((x <= a && a <= y) ? "NO" : "YES");
  }
}
