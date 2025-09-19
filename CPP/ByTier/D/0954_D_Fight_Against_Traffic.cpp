/*
 * Problem URL : https://codeforces.com/problemset/problem/954/D
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;

int q[1010], d1[1010], d2[1010], g[1010][1010], n, m, s, t, cnt;
void bfs(int s, int *d) {
  memset(d, 0x3f, 1010 * 4);
  int tt = -1, ww = 0;
  q[0] = s;
  d[s] = 0;
  while (tt < ww) {
    int x = q[++tt];
    for (int i = 1; i <= n; i++)
      if (g[x][i] && d[i] == 0x3f3f3f3f) {
        d[i] = d[x] + 1;
        q[++ww] = i;
      }
  }
}
int main() {
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u][v] = g[v][u] = 1;
  }
  bfs(s, d1);
  bfs(t, d2);
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      if (d1[i] + d2[j] + 1 >= d1[t] && d2[i] + d1[j] + 1 >= d1[t] && !g[i][j])
        cnt++;
  cout << cnt << endl;
  return 0;
}