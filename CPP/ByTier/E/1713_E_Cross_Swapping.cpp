/*
 * Problem URL : https://codeforces.com/problemset/problem/1713/E
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
const int N = 1000;
inline char nc() {
  static char buf[99999], *l, *r;
  return l == r && (r = (l = buf) + fread(buf, 1, 99999, stdin), l == r) ? EOF
                                                                         : *l++;
}
inline void read(int &x) {
  char c = nc();
  for (; c < '0' || '9' < c; c = nc())
    ;
  for (x = 0; '0' <= c && c <= '9';
       x = (x << 3) + (x << 1) + (c ^ 48), c = nc())
    ;
}
int t, n, a[N][N], f[N], ff[N];
inline int find(const int &x) {
  if (x == f[x])
    return x;
  int tmp = find(f[x]);
  ff[x] ^= ff[f[x]];
  return f[x] = tmp;
}
main() {
  for (read(t); t--;) {
    read(n);
    for (int i = 0; i < n; f[i] = i, ff[i++] = 0)
      for (int j = 0; j < n; read(a[i][j++]))
        ;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (i ^ j)
          if (find(i) ^ find(j)) {
            if (a[i][j] < a[j][i]) {
              ff[f[i]] = ff[i] ^ ff[j];
              f[f[i]] = f[j];
            }
            if (a[i][j] > a[j][i]) {
              ff[f[i]] = ff[i] ^ ff[j] ^ 1;
              f[f[i]] = f[j];
            }
          }
    for (int i = 0; i < n; ++i)
      if (find(i), ff[i])
        for (int j = 0; j < n; ++j)
          if (i ^ j)
            a[i][j] ^= a[j][i] ^= a[i][j] ^= a[j][i];
    for (int i = 0; i < n; putchar('\n'), ++i)
      for (int j = 0; j < n; printf("%d ", a[i][j++]))
        ;
  }
}