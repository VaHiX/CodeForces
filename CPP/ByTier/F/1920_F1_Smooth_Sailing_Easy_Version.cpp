// Problem: CF 1920 F1 - Smooth Sailing (Easy Version)
// https://codeforces.com/contest/1920/problem/F1

/*
 * Problem: F1. Smooth Sailing (Easy Version)
 * 
 * Purpose: 
 * This code solves the problem of finding the maximum safety of round trips 
 * starting from given positions on a grid, where:
 * - Grid consists of ocean ('.'), island ('#'), and underwater volcano ('v') cells
 * - A round trip must encircle the island
 * - Safety is the minimum Manhattan distance from any point on the trip to a volcano
 * 
 * Algorithm:
 * 1. Multi-source BFS from all volcano cells to compute distances to nearest volcano
 * 2. Union-Find with modifications to track connected components and maximum safety
 * 3. Process grid cells in order of increasing distance from volcano
 * 
 * Time Complexity: O(n * m * log(n * m))
 * Space Complexity: O(n * m)
 * 
 * Techniques:
 * - Multi-source BFS to compute Manhattan distances
 * - Union-Find with path compression and union by size
 * - Progressive processing based on distance from volcanoes
 */

#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
int m, n, q, ans[300001], fa[600001], val[300001];
vector<char> a[100002];
vector<int> d[100001], id[600001];
vector<pair<int, int>> g[300001];
queue<pair<int, int>> qu;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int find_parent(int x) {
  if (x == fa[x]) {
    return x;
  } else {
    fa[x] = find_parent(fa[x]);
    return fa[x];
  }
}
void find_union(int x, int y, int t) {
  x = find_parent(x);
  y = find_parent(y);
  if (x == y) {
    return;
  }
  // Union by size
  if (id[x].size() < id[y].size()) {
    x = x + y;
    y = x - y;
    x = x - y;
  }
  fa[y] = x;
  // Update answer for all queries in the smaller component
  for (int i : id[y]) {
    id[x].push_back(i);
    // Check if vertex is currently part of island boundary
    if (find_parent(val[i]) == find_parent(val[i] + m * n)) {
      if (t > ans[i]) {
        ans[i] = t;
      }
    }
  }
  id[y].clear();
}
int main() {
  scanf("%d %d %d", &n, &m, &q);
  int tx = 0, ty = 0;
  for (int i = 1; i <= n; i++) {
    a[i].resize(m + 1);
    d[i].resize(m + 1);
    scanf("\n");
    for (int j = 1; j <= m; j++) {
      scanf("%c", &a[i][j]);
      d[i][j] = 1000000000;
      if (a[i][j] == 'v') {
        qu.push({i, j});
        d[i][j] = 0;
      } else if (a[i][j] == '#') {
        tx = i;
        ty = j;
      }
      int x = (i - 1) * m + j;
      fa[x] = x;
      fa[x + m * n] = x + m * n;
    }
  }
  // Multi-source BFS to compute distances to nearest volcano
  while (!qu.empty()) {
    int x = qu.front().first;
    int y = qu.front().second;
    qu.pop();
    if (a[x][y] != '#') {
      g[d[x][y]].push_back({x, y});
    }
    for (int i = 0; i < 4; i++) {
      int nx = x + dir[i][0];
      int ny = y + dir[i][1];
      if (nx > 0 && nx <= n && ny > 0 && ny <= m && d[x][y] + 1 < d[nx][ny]) {
        d[nx][ny] = d[x][y] + 1;
        qu.push({nx, ny});
      }
    }
  }
  // Initialize query positions
  for (int i = 1; i <= q; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    val[i] = (x - 1) * m + y;
    id[val[i]].push_back(i);
    id[val[i] + m * n].push_back(i);
  }
  // Process from largest distance to smallest
  for (int i = m * n; i >= 0; i--) {
    for (auto it : g[i]) {
      int x = it.first;
      int y = it.second;
      for (int j = 0; j < 4; j++) {
        int nx = x + dir[j][0];
        int ny = y + dir[j][1];
        if (nx > 0 && nx <= n && ny > 0 && ny <= m && a[nx][ny] != '#' &&
            d[x][y] <= d[nx][ny]) {
          // Determine which side of the island the union is on
          int w = ((x == tx && nx == tx + 1 && y > ty) ||
                   (x == tx + 1 && nx == tx && ny > ty));
          find_union((x - 1) * m + y, (nx - 1) * m + ny + w * m * n, i);
          find_union((x - 1) * m + y + m * n,
                     (nx - 1) * m + ny + (1 - w) * m * n, i);
        }
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/