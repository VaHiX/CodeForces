/*
 * Problem URL : https://codeforces.com/problemset/problem/1744/A
 * Submit Date : 2025-08-21
 */

#include <cstring>
#include <stdio.h>
int main() {
  int t, n, f, i, a[52], b[52];
  char s[51];
  scanf("%d", &t);
  while (t--) {
    memset(b, 0, sizeof(b)), scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    scanf("%s", s);
    for (f = i = 0; i < n; ++i)
      b[a[i]] && b[a[i]] - s[i] ? f = 1 : b[a[i]] = s[i];
    puts(f ? "NO" : "YES");
  }
}
