/*
 * Problem URL : https://codeforces.com/contest/2073/problem/L
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define N 1005
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int r, c, n, p, i, j, g[N][N], x, y, vis[N * N], t;
  cin >> r >> c >> n >> p;
  for (i = 0; i <= r + 1; i++)
    for (j = 0; j <= c + 1; j++)
      g[i][j] = 0;
  for (i = 1; i <= n; i++)
    vis[i] = 0;
  for (i = 1; i <= r; i++)
    for (j = 1; j <= c; j++)
      cin >> g[i][j];
  for (i = 1; i <= r; i++)
    for (j = 1; j <= c; j++)
      if (p == g[i][j]) {
        x = i;
        y = j;
      }
  t = 0;
  while (true) {
    if (g[x - 1][y] && g[x - 1][y] + t <= n)
      vis[g[x - 1][y] + t] = 1;
    if (g[x][y - 1] && g[x][y - 1] + t <= n)
      vis[g[x][y - 1] + t] = 1;
    if (g[x + 1][y] && g[x + 1][y] + t <= n)
      vis[g[x + 1][y] + t] = 1;
    if (g[x][y + 1] && g[x][y + 1] + t <= n)
      vis[g[x][y + 1] + t] = 1;
    if (g[x][y] == 1)
      break;
    if (g[x - 1][y] == g[x][y] - 1)
      x--;
    else if (g[x][y - 1] == g[x][y] - 1)
      y--;
    else if (g[x + 1][y] == g[x][y] - 1)
      x++;
    else
      y++;
    t++;
  }
  x = 0;
  y = n - 1;
  for (i = 1; i <= n; i++)
    x += vis[i];
  cout << x << '/' << y;
  return 0;
}
