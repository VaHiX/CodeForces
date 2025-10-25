/*
 * Problem URL : https://codeforces.com/contest/1089/problem/M
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
int n;
char s[3][27][27];
int main() {
  scanf("%d", &n);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3 * n; j++)
      fill(s[i][j], s[i][j] + 3 * n, '#');
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3 * n; j++) {
      s[0][i * 3][j] = s[2][j][i * 3] = '.';
    }
    s[1][i * 3][i * 3 + 1] = s[1][i * 3 + 1][i * 3 + 1] =
        s[2][i * 3 + 1][i * 3 + 1] = '.';
    for (int j = 0, ti; j < n; j++) {
      scanf("%d", &ti);
      if (ti) {
        for (int k = 0; k < 3; k++)
          s[k][i * 3 + 1][j * 3 + 1] = '.';
      }
    }
    s[0][i * 3][n * 3 - 1] = i + '1';
  }
  printf("%d %d %d\n", n * 3, n * 3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3 * n; j++) {
      for (int k = 0; k < 3 * n; k++) {
        putchar(s[i][j][k]);
      }
      putchar('\n');
    }
    if (i != 2)
      putchar('\n');
  }
  return 0;
}