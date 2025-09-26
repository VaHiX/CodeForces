/*
 * Problem URL : https://codeforces.com/contest/891/problem/A
 * Submit Date : 2025-09-04
 */

#include <algorithm>
#include <cstdio>
int n, r, i, j, a[2000];
int g() {
  if (r)
    return n - r;
  for (i = 1; i < n; ++i)
    for (j = 0; j + i < n; ++j)
      if ((a[j] = std::__gcd(a[j], a[j + 1])) == 1)
        return i + n - 1;
  return -1;
}
main() {
  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d", a + i);
    if (a[i] == 1)
      ++r;
  }
  printf("%d", g());
}