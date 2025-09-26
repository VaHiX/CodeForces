/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  int girlLeft(0), girlRight(0);
  scanf("%d %d", &girlLeft, &girlRight);
  int boyLeft(0), boyRight(0);
  scanf("%d %d", &boyLeft, &boyRight);

  if ((girlLeft - 1 <= boyRight && boyRight <= 2 * (girlLeft + 1)) ||
      (girlRight - 1 <= boyLeft && boyLeft <= 2 * (girlRight + 1))) {
    puts("YES");
  } else {
    puts("NO");
  }

  return 0;
}
