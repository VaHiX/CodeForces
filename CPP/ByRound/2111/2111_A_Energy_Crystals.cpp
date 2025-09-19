/*
 * Problem URL : https://codeforces.com/problemset/problem/2111/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    long g(1), cnt(0);
    while (g < x) {
      g = 2 * g + 1;
      ++cnt;
    }
    printf("%ld\n", 2 * cnt + 3);
  }
}
