/*
 * Problem URL : https://codeforces.com/problemset/problem/1924/A
 * Submit Date : 2025-08-20
 */

#include <cstdio>
const int N = 100002;
int T, n, k, m, i, j, p, x;
char s[N], s2[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%s", &n, &k, &m, s + 1);
    p = x = 0;
    for (i = 1; i <= m; i++) {
      p |= 1 << (s[i] - 'a');
      if (p == (1 << k) - 1) {
        p = 0;
        s2[++x] = s[i];
      }
    }
    if (x >= n)
      printf("YES\n");
    else {
      printf("NO\n");
      for (i = 0; i < k; i++)
        if ((p & 1 << i) == 0) {
          s2[++x] = i + 'a';
          break;
        }
      while (x < n)
        s2[++x] = 'a';
      s2[x + 1] = 0;
      printf("%s\n", s2 + 1);
    }
  }
}
