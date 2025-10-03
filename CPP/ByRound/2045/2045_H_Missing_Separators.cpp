/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <cstdio>
#include <cstring>
const int N = 5005;
int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }
int n, f[N][N];
int lcp[N][N];
char s[N];
int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = n; i; i--)
    for (int j = n; j; j--)
      lcp[i][j] = (s[i] == s[j]) * (lcp[i + 1][j + 1] + 1);
  for (int i = n; i; i--) {
    for (int j = n; j >= i; j--) {
      int u = min(j - i + 1, lcp[i][j + 1]);
      if (i + u <= j && j + 1 + u <= n && s[i + u] < s[j + 1 + u])
        f[i][j] = f[j + 1][j + 1 + u];
      if (i + u > j && j + 1 + u <= n)
        f[i][j] = f[j + 1][j + 1 + u];
      f[i][j] = max(f[i][j] + 1, f[i][j + 1]);
    }
  }
  printf("%d\n", f[1][1]);
  for (int i = f[1][1], j = 1; i; i--) {
    int k = j;
    while (k < n && f[j][k + 1] >= i)
      k++;
    for (int h = j; h <= k; h++)
      putchar(s[h]);
    j = k + 1;
    putchar(10);
  }
}