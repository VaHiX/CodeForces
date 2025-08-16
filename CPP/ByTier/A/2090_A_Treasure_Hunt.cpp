/*
 * Problem URL : https://codeforces.com/problemset/problem/2090/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, a;
    scanf("%ld %ld %ld", &x, &y, &a);
    a %= (x + y);
    puts(a < x ? "NO" : "YES");
  }
}
