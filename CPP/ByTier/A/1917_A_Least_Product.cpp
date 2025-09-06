/*
 * Problem URL : https://codeforces.com/problemset/problem/1917/A
 * Submit Date : 2025-08-20
 */

#include <stdio.h>
void work() {
  int n, x, t = 0, f = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    if (x < 0)
      t ^= 1;
    if (x == 0)
      f = 1;
  }
  if (f || t)
    puts("0");
  else
    printf("1\n1 0\n");
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    work();
}