/*
 * Problem URL : https://codeforces.com/contest/1132/problem/A
 * Submit Date : 2025-08-28
 */

#include <cstdio>

int main() {

  long a, b, c, d;
  scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
  int ans(1);
  if (a != d) {
    ans = 0;
  }
  if (c && !a) {
    ans = 0;
  }
  printf("%d\n", ans);

  return 0;
}
