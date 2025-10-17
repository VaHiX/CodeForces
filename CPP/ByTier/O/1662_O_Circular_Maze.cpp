/*
 * Problem URL : https://codeforces.com/contest/1662/problem/O
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
#define use 1, n, rt
#define left l, mid, ls[p]
#define righ mid + 1, r, rs[p]
#define N 500000
#define fer(x, y, z) for (register int x = y; x <= z; x++)
using namespace std;
int t, n;
bool pd[41][361 * 2], vis[41][361 * 2];
int sak_dfs(int x, int y) {

  if (x == 40) {
    return true;
  }
  vis[x][y] = 1;
  int flag = 0;
  if (y == 1) {
    if (!pd[x][720] && !vis[x][720])
      flag += sak_dfs(x, 720);
  } else if (!pd[x][y - 1] && !vis[x][y - 1])
    flag += sak_dfs(x, y - 1);
  if (y == 720) {
    if (!pd[x][1] && !vis[x][1])
      flag += sak_dfs(x, 1);
  } else if (!pd[x][y + 1] && !vis[x][y + 1])
    flag += sak_dfs(x, y + 1);
  if (x != 1 && !pd[x - 1][y] && !vis[x - 1][y])
    flag += sak_dfs(x - 1, y);
  if (!pd[x + 1][y] && !vis[x + 1][y])
    flag += sak_dfs(x + 1, y);
  return flag != 0;
}
signed main() {
  cin >> t;
  while (t--) {
    char ch;
    int x, y, z;
    cin >> n;
    memset(pd, 0, sizeof pd), memset(vis, 0, sizeof vis);
    fer(i, 1, n) {
      scanf(" %c%d%d%d", &ch, &x, &y, &z);
      x *= 2;
      y *= 2, z *= 2;
      if (ch == 'C') {
        y += 2, z += 2;
        if (y > z) {

          fer(i, y, 720) pd[x][i] = 1;
          fer(i, 1, z) pd[x][i] = 1;
        } else
          fer(i, y, z) pd[x][i] = 1;
      } else
        fer(i, x, y) pd[i][z + 2] = 1;
    }
    if (sak_dfs(1, 1))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}
