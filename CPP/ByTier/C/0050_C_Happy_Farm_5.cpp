/*
 * Problem URL : https://codeforces.com/problemset/problem/50/C
 * Submit Date : 2025-08-13
 */

#include <cstdio>
#include <iostream>
using namespace std;
int mx = 0x3f3f3f3f;
int a = -mx, b = -mx, c = mx, d = mx, x, y, n;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x, &y);
    a = max(a, x - y);
    b = max(b, x + y);
    c = min(c, x + y);
    d = min(d, x - y);
  }
  int ans = a + b - c - d + 4;
  printf("%d", ans);
}
