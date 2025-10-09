/*
 * Problem URL : https://codeforces.com/contest/1257/problem/B
 * Submit Date : 2025-08-28
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    bool ans(true);
    if (x == 1) {
      ans = (y == 1);
    } else if (x == 2 || x == 3) {
      ans = (y <= 3);
    }
    puts(ans ? "YES" : "NO");
  }

  return 0;
}
