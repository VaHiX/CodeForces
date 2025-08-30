/*
 * Problem URL : https://codeforces.com/problemset/problem/2060/E
 * Submit Date : 2025-08-23
 */

#include <stdio.h>

const int N = 2e5 + 5;
int g[N], f[N], a[N], b[N], n, m1, m2;
int hg[N], hf[N];
int findg(int x) {
  if (g[x] == x)
    return x;
  return g[x] = findg(g[x]);
}
int findf(int x) {
  if (f[x] == x)
    return x;
  return f[x] = findf(f[x]);
}
void sol() {
  scanf("%d%d%d", &n, &m1, &m2);
  for (int i = 1; i <= n; ++i) {
    hg[i] = hf[i] = 0;
    g[i] = f[i] = i;
  }
  int s1 = 0, s2 = 0, s3 = 0;
  for (int i = 1; i <= m1; ++i)
    scanf("%d%d", &a[i], &b[i]);
  for (int i = 1; i <= m2; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[findg(x)] = findg(y);
  }
  for (int i = 1; i <= n; ++i)
    if (!hg[findg(i)]) {
      hg[findg(i)] = 1;
      ++s3;
    }
  for (int i = 1; i <= m1; ++i) {
    if (findg(a[i]) == findg(b[i]))
      f[findf(a[i])] = findf(b[i]);
    else
      ++s1;
  }
  for (int i = 1; i <= n; ++i)
    if (!hf[findf(i)]) {
      hf[findf(i)] = 1;
      ++s2;
    }
  printf("%d\n", s1 + s2 - s3);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
}