/*
 * Problem URL : https://codeforces.com/problemset/problem/1478/F
 * Submit Date : 2025-08-13
 */

#include <stdio.h>
#define ll (long long)
struct mp {
  int x, y, idx;
} a[5005];
bool dot(mp a, mp b, mp c) {
  return ll(b.x - a.x) * ll(c.x - a.x) + ll(b.y - a.y) * ll(c.y - a.y) <= 0;
}
int main() {
  int n, i, j;
  mp x;
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d%d", &a[i].x, &a[i].y), a[i].idx = i;
  for (i = 3; i <= n; i++)
    for (j = i; j >= 3; j--)
      if (dot(a[j - 1], a[j], a[j - 2]))
        x = a[j], a[j] = a[j - 1], a[j - 1] = x;
      else
        break;
  printf("%d", a[1].idx);
  for (i = 2; i <= n; i++)
    printf(" %d", a[i].idx);
  return 0;
}
