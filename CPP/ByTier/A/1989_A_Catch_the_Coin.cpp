/*
 * Problem URL : https://codeforces.com/problemset/problem/1989/A
 * Submit Date : 2025-08-11
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    puts(y >= -1 ? "YES" : "NO");
  }
}
