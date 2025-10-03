/*
 * Problem URL : https://codeforces.com/problemset/problem/911/A
 * Submit Date : 2025-08-20
 */

#include <cstdio>
int main() {
  int n, x, min, min2, p = 0;
  scanf("%d%d", &n, &min);
  min2 = n;
  for (int i = 1; i < n; i++) {
    scanf("%d", &x);
    if (x < min) {
      min = x;
      min2 = n;
      p = i;
    } else if (x == min) {
      if (i - p < min2)
        min2 = i - p;
      p = i;
    }
  }
  printf("%d\n", min2);
  return 0;
}