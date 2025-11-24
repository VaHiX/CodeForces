// Problem: CF 2109 F - Penguin Steps
// https://codeforces.com/contest/2109/problem/F

/*
Algorithm: Binary search on answer with Dijkstra optimization
Purpose: Given a grid with colored cells, find minimum cost paths for two players
         and optimize one player's operation to maximize the other's cost.
         Mouf starts from (1,1) and Fouad from (n,1), both going to (r,n).
         Mouf can perform up to k operations to increment values of black cells.
         We need to find the minimum cost paths for both and maximize 
         Fouad's cost while ensuring Mouf's cost stays constant.
Time Complexity: O(n^2 * log(max_val + k) * log(n^2))
Space Complexity: O(n^2)
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;
constexpr int inf = 0x3f3f3f3f;
struct node {
  int x, y, dis;
  bool operator>(const node &x) const { return dis > x.dis; }
};
int t, n, r, k, a[305][305], dism, dx[8] = {1, -1, 0, 0, 1, 1, -1, -1},
                                   dy[8] = {0, 0, 1, -1, 1, -1, 1, -1},
                                   val[305][305], dis[305][305];
bool vis[305][305], able[305][305], mark[305][305];
string s;
inline bool can(int x, int y) { return x > 0 && y > 0 && x <= n && y <= n; }
bool check(int x) {
  // Initialize cost values for each cell based on threshold x
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      // If cell is white or value is >= x, we can take it at cost (x - value)
      // Otherwise cost is infinity (not reachable)
      val[i][j] = able[i][j] || a[i][j] >= x ? max(0, x - a[i][j]) : inf;
      dis[i][j] = inf, vis[i][j] = 0;
    }
  }
  // If x > dism, we must not use operations on cells that contribute to path
  if (x > dism)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        if (mark[i][j])
          val[i][j] = inf;
  // Dijkstra with priority queue
  priority_queue<node, vector<node>, greater<node>> p;
  // Start from starting positions
  for (int i = 1; i <= n; i++)
    p.emplace(node{1, i, dis[1][i] = val[1][i]}),
        p.emplace(node{i, 1, dis[i][1] = val[i][1]});
  // Target positions
  for (int i = 2; i <= r; i++)
    p.emplace(node{i, n, dis[i][n] = val[i][n]});
  while (!p.empty()) {
    node v = p.top();
    p.pop();
    if (vis[v.x][v.y])
      continue;
    vis[v.x][v.y] = 1;
    // Move in 8 directions
    for (int i = 0; i < 8; i++) {
      int tx = v.x + dx[i], ty = v.y + dy[i];
      if (can(tx, ty) && v.dis + val[tx][ty] < dis[tx][ty])
        p.emplace(node{tx, ty, dis[tx][ty] = v.dis + val[tx][ty]});
    }
  }
  int minx = inf;
  // Find minimum cost to reach any valid exit position
  for (int i = 1; i <= n; i++)
    minx = min(minx, dis[n][i]);
  for (int i = r; i < n; i++)
    minx = min(minx, dis[i][n]);
  return minx <= k;
}
int ef(int l, int r) {
  // Binary search on the answer
  while (l < r) {
    int mid = (l + r + 1) >> 1;
    if (check(mid))
      l = mid;
    else
      r = mid - 1;
  }
  return l;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> r >> k;
    // Read grid values
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        cin >> a[i][j];
    // Read color information (black = 1, white = 0)
    for (int i = 1; i <= n; i++) {
      cin >> s;
      for (int j = 1; j <= n; j++)
        able[i][j] = s[j - 1] ^ 48, mark[i][j] = vis[i][j] = 0, dis[i][j] = inf;
    }
    // Dijkstra to find minimal path for Mouf from (1,1) to (r,n)
    priority_queue<node, vector<node>, greater<node>> p;
    p.emplace(node{1, 1, dis[1][1] = a[1][1]});
    while (!p.empty()) {
      node v = p.top();
      p.pop();
      if (vis[v.x][v.y])
        continue;
      vis[v.x][v.y] = 1;
      // Move in 4 directions only (up, down, left, right)
      for (int i = 0; i < 4; i++) {
        int tx = v.x + dx[i], ty = v.y + dy[i];
        if (can(tx, ty) && max(v.dis, a[tx][ty]) < dis[tx][ty])
          p.emplace(node{tx, ty, dis[tx][ty] = max(v.dis, a[tx][ty])});
      }
    }
    dism = dis[r][n]; // Cost for Mouf to reach target
    queue<pair<int, int>> q;
    // Mark all cells that are on (or can reach) the target path
    for (int i = 1; i <= n; i++)
      mark[1][i] = 1, q.emplace(make_pair(1, i));
    for (int i = 2; i <= r; i++)
      mark[i][n] = 1, q.emplace(make_pair(i, n));
    // BFS to identify all cells that could influence the path
    while (!q.empty()) {
      pair<int, int> v = q.front();
      q.pop();
      if (a[v.first][v.second] <= dism)
        continue;
      for (int i = 0; i < 8; i++) {
        int tx = v.first + dx[i], ty = v.second + dy[i];
        if (can(tx, ty) && !mark[tx][ty])
          mark[tx][ty] = 1, q.emplace(make_pair(tx, ty));
      }
    }
    // Binary search to find maximum possible cost for Fouad
    cout << dism << ' ' << ef(1, 1000000 + k) << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/