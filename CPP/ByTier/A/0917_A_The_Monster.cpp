/*
 * Problem URL : https://codeforces.com/contest/917/problem/A
 * Submit Date : 2025-09-04
 */

#include <cstdio>
#include <cstring>
char s[5050];
int main() {
  scanf("%s", s);
  int i, j, l, r, n, ans = 0;
  n = strlen(s);
  for (i = 0; i < n; i++) {
    l = 0, r = 0;
    for (j = i; j < n; j++) {
      (s[j] == '(' ? l++ : l--);
      (s[j] == ')' ? r-- : r++);
      if (l < 0)
        l = 1;
      if (r < 0)
        break;
      if (l == 0)
        ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}
