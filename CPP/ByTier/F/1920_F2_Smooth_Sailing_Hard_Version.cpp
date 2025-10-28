// Problem: CF 1920 F2 - Smooth Sailing (Hard Version)
// https://codeforces.com/contest/1920/problem/F2

/*
Problem: F2. Smooth Sailing (Hard Version)
Algorithm: Union-Find with path compression and union by size, BFS for distance calculation
Time Complexity: O(n * m * α(n * m)) where α is the inverse Ackermann function, practically constant
Space Complexity: O(n * m)

This solution uses a union-find data structure to track the minimum distance to any volcano
for different segments of the ocean around the island. The key insight is to build a 
disjoint set forest where each set represents a connected component of ocean/volcano cells
that can be reached with the same minimum distance to a nearby volcano.

The algorithm:
1. Use BFS to compute distance from each ocean/volcano cell to the nearest volcano
2. Build a union-find structure where we connect cells that are at the same distance level
3. For each query, find the minimum distance from the queried point to any volcano by 
   traversing the union-find structure

*/
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#define fi first
#define se second
using namespace std;
const int INF = -1e8;
vector<int> Fa, T;
int find(int x) { return Fa[x] < 0 ? x : find(Fa[x]); }
void uni(int u, int v, int t) {
  u = find(u), v = find(v);
  if (u == v)
    return;
  if (-Fa[u] > -Fa[v])
    swap(u, v);
  Fa[v] += Fa[u], Fa[u] = v, T[u] = t;
}
int ask(int u, int v) {
  int t = 0;
  while (u != v) {
    int &x = T[u] > T[v] ? u : v;
    t = T[x], x = Fa[x];
    if (t == INF)
      return -1;
  }
  return t;
}
void solve() {
  int n, m, a;
  cin >> n >> m >> a;
  Fa.assign(2 * n * m, -1);
  T.assign(2 * n * m, INF);
  vector<string> v(n);
  for (auto &r : v)
    cin >> r;
  int xc = 0, yc = 0;
  vector<pair<int, int>> o;
  int x[4] = {1, 0, -1, 0}, y[4] = {0, 1, 0, -1};
  vector<vector<int>> d(n, vector<int>(m, -1));
  queue<pair<int, int>> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (v[i][j] == '#') {
        xc = i;
        yc = j;
      }
      if (v[i][j] == 'v') {
        q.push({i, j});
        d[i][j] = 0;
      }
    }
  }
  while (!q.empty()) {
    int cx = q.front().fi, cy = q.front().se;
    q.pop();
    if (v[cx][cy] != '#')
      o.push_back({cx, cy});
    for (int i = 0; i < 4; i++) {
      int nx = cx + x[i], ny = cy + y[i];
      if (~nx && nx < n && ~ny && ny < m && d[nx][ny] < 0) {
        d[nx][ny] = 1 + d[cx][cy];
        q.push({nx, ny});
      }
    }
  }
  for (int i = xc + 1; i < n; i++)
    v[i][yc] = 0;
  for (int j = o.size() - 1; ~j; j--) {
    int cx = o[j].fi, cy = o[j].se;
    for (int i = 0; i < 4; i++) {
      int nx = cx + x[i], ny = cy + y[i];
      if (~nx && nx < n && ~ny && ny < m && d[nx][ny] >= d[cx][cy] &&
          v[nx][ny] != '#') {
        if (!v[cx][cy] && i == 1 || !v[nx][ny] && i == 3) {
          uni(nx * m + ny + n * m, cx * m + cy, d[cx][cy]);
          uni(nx * m + ny, cx * m + cy + n * m, d[cx][cy]);
        } else {
          uni(nx * m + ny, cx * m + cy, d[cx][cy]);
          uni(nx * m + ny + n * m, cx * m + cy + n * m, d[cx][cy]);
        }
      }
    }
  }
  while (a--) {
    int cx, cy;
    cin >> cx >> cy;
    cx--;
    cy--;
    cout << ask(cx * m + cy, cx * m + cy + n * m) << "\n";
  }
}
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T = 1;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/