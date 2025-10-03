/*
 * Problem URL : https://codeforces.com/contest/1070/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
#define max_n 2000
int TID;
int n;
int m;
bitset<max_n + 2> g[max_n + 2];
int de[max_n + 2];
bool ans1;
bool ans[max_n + 2];
int main() {
#ifndef ONLINE_JUDGE
  freopen("CF1070L_1.in", "r", stdin);
  freopen("CF1070L_1.out", "w", stdout);
#endif
  scanf("%d", &TID);
  while (TID--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      g[i].reset();
    memset(de, 0, sizeof(de));
    for (int i = 1, u, v; i <= m; ++i) {
      scanf("%d%d", &u, &v);
      g[u][v] = g[v][u] = 1;
      ++de[u];
      ++de[v];
    }
    ans1 = true;
    for (int i = 1; i <= n; ++i) {
      if (de[i] & 1) {
        ans1 = false;
        break;
      }
    }
    if (ans1) {
      printf("1\n");
      for (int i = 1; i <= n; ++i)
        printf("%d ", 1);
      printf("\n");
      continue;
    }
    for (int i = 1; i <= n; ++i)
      g[i][i] = g[i][n + 1] = de[i] & 1;
    for (int i = 1, r; i <= n; ++i) {
      r = 0;
      for (int j = i; j <= n; ++j) {
        if (g[j][i]) {
          r = j;
          break;
        }
      }
      swap(g[i], g[r]);
      for (int j = i + 1; j <= n; ++j) {
        if (g[j][i])
          g[j] ^= g[i];
      }
    }
    for (int i = n; i >= 1; --i) {
      ans[i] = g[i][n + 1];
      for (int j = i + 1; j <= n; ++j) {
        if (g[i][j])
          ans[i] ^= ans[j];
      }
    }
    printf("2\n");
    for (int i = 1; i <= n; ++i) {
      if (ans[i])
        printf("1 ");
      else
        printf("2 ");
    }
    printf("\n");
  }
  return 0;
}
