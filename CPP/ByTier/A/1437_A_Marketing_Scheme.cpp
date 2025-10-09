/*
 * Problem URL : https://codeforces.com/problemset/problem/1437/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    puts(r + 1 <= 2 * l ? "YES" : "NO");
  }

  return 0;
}
