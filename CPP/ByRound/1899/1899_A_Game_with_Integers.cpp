/*
 * Problem URL : https://codeforces.com/problemset/problem/1899/A
 * Submit Date : 2025-08-14
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    puts(x % 3 == 0 ? "Second" : "First");
  }
}
