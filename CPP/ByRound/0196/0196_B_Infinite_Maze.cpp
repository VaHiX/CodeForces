/*
 * Problem URL : https://codeforces.com/problemset/problem/196/B
 * Submit Date : 2025-08-08
 */

#include <iostream>
using namespace std;
const int M = 1600;
int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
int n, m, pr[M][M], pc[M][M];
char g[M][M], f[M][M];
bool dfs(int r, int c) {
  int u = (r % n + n) % n, v = (c % m + m) % m;
  if ('#' == g[u][v])
    return 0;
  if (f[u][v])
    return r != pr[u][v] || c != pc[u][v];
  f[u][v] = 1, pr[u][v] = r, pc[u][v] = c;
  for (int d = 0; d < 4; ++d)
    if (dfs(r + dr[d], c + dc[d]))
      return 1;
  return 0;
}
int main(void) {
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> g[i];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if ('S' == g[i][j])
        cout << (dfs(i + n * 2, j + m * 2) ? "Yes" : "No") << endl;
}
