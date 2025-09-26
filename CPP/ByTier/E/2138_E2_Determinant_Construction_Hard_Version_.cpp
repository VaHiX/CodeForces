/*
 * Problem URL : https://codeforces.com/contest/2138/problem/E2
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
const int N = 100;
int K;
int n;
int a[N + 5][N + 5];
int b[N + 5];
int g[N + 5];
void clean() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      a[i][j] = 0;
  for (int i = 0; i <= 25; ++i)
    b[i] = g[i] = 0;
  n = 0;
}
void work() {
  scanf("%d", &K);
  if (!K) {
    printf("1\n0\n");
    return;
  }
  if (K == 1) {
    printf("1\n1\n");
    return;
  }
  for (int i = 0; i <= 25; ++i) {
    b[i] = (K >> i) & 1;
  }
  for (int i = 0; i <= 25; ++i) {
    if (b[i] == 1 && b[i + 1] == 1) {
      for (int j = i + 1; j <= 25; ++j)
        if (b[j] == 1 && b[j + 1] == 0 && b[j + 2] == 0) {
          g[j + 1] = 1;
          for (int k = i + 2; k <= j; ++k)
            if (b[k] == 0)
              g[k] = -1;
          g[i] = -1;
          i = j + 2;
          break;
        }
    } else if (b[i] == 1) {
      g[i] = 1;
    }
  }
  // for(int i=10;~i;--i)printf("%d ",g[i]);
  // printf("\n");
  for (int i = 25; ~i; --i) {
    if (g[i] == 1) {
      n = i * 2;
      break;
    }
  }
  // printf("%d\n",n);
  for (int i = 1; i <= n / 2; ++i) {
    a[i * 2][i * 2] = 1;
    a[i * 2 - 1][i * 2 - 1] = 1;
    a[i * 2 - 1][i * 2] = 1;
    a[i * 2][i * 2 - 1] = -1;
    if (i * 2 + 1 <= n)
      a[i * 2][i * 2 + 1] = 1;
  }
  for (int i = 0, x = n - 1, y = 2; i <= n / 2 - 1; ++i) {
    if (g[i]) {
      a[x][y] = (1 - ((x - y) & 1) * 2) * g[i];
    }
    if (i & 1)
      x -= 2;
    else
      y += 2;
  }
  printf("%d\n", n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}
int Tcase;
int main() {
  scanf("%d", &Tcase);
  while (Tcase--) {
    clean();
    work();
  }
  return 0;
}