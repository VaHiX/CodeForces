/*
 * Problem URL : https://codeforces.com/contest/2041/problem/D
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
using VI = vector<int>;
using PI = pair<int, int>;
int n, m, fx[4] = {0, 0, 1, -1}, fy[4] = {1, -1, 0, 0};
int stx, sty, enx, eny;
struct node {
  int x, y, lst, dep, cnt;
};
queue<node> q;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  char c[n + 1][m + 1];
  bool vis[n + 1][m + 1][4][4];
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= m; j++) {
      c[i][j] = s[j - 1];
      if (s[j - 1] == 'S') {
        q.push({i, j, 0, 0});
        stx = i;
        sty = j;
        c[i][j] = '#';
      }
      if (s[j - 1] == 'T') {
        enx = i;
        eny = j;
        c[i][j] = '.';
      }
    }
  }
  while (!q.empty()) {
    node u = q.front();
    q.pop();
    if (u.x == enx && u.y == eny) {
      cout << u.dep;
      return 0;
    }
    for (int i = 0; i < 4; i++) {
      int xx = u.x + fx[i], yy = u.y + fy[i];
      if (xx < 1 || xx > n || yy < 1 || yy > m || c[xx][yy] != '.')
        continue;
      if (u.lst == i) {
        if (u.cnt + 1 < 4 && !vis[xx][yy][i][u.cnt + 1]) {
          vis[xx][yy][i][u.cnt + 1] = 1;
          q.push({xx, yy, i, u.dep + 1, u.cnt + 1});
        }
      } else if (!vis[xx][yy][i][1]) {
        vis[xx][yy][i][1] = 1;
        q.push({xx, yy, i, u.dep + 1, 1});
      }
    }
  }
  cout << -1;
  return 0;
}