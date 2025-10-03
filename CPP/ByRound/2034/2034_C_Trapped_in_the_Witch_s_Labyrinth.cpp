/*
 * Problem URL : https://codeforces.com/contest/2034/problem/C
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, m;
char a[1001][1001];
int b[1001][1001];
bool dfs(int x, int y) {
  if (!x || !y || x > n || y > m) {
    return 1;
  }
  if (b[x][y] != -1) {
    return b[x][y];
  }
  b[x][y] = 0;
  if (a[x][y] == 'U') {
    return b[x][y] = dfs(x - 1, y);
  }
  if (a[x][y] == 'D') {
    return b[x][y] = dfs(x + 1, y);
  }
  if (a[x][y] == 'L') {
    return b[x][y] = dfs(x, y - 1);
  }
  if (a[x][y] == 'R') {
    return b[x][y] = dfs(x, y + 1);
  }
  if (a[x][y] == '?') {
    return b[x][y] =
               dfs(x - 1, y) && dfs(x + 1, y) && dfs(x, y - 1) && dfs(x, y + 1);
  }
}
int main() {
  t = 1;
  scanf("%d", &t);
  for (; t--;) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%s", a[i] + 1);
      for (int j = 1; j <= m; j++) {
        b[i][j] = -1;
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        ans += !dfs(i, j);
      }
    }
    printf("%d\n", ans);
  }
}