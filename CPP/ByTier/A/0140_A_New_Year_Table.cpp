/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>

int main() {

  int n(0), R(0), r(0);
  scanf("%d %d %d", &n, &R, &r);
  const double PI = 3.14159265359;
  if ((n == 1 && r <= R) || (n == 2 && 2 * r <= R) ||
      (n >= 3 && r < R && sin(PI / n) >= 1.0 * r / (1.0 * R - r))) {
    puts("YES");
  } else {
    puts("NO");
  }
  return 0;
}
