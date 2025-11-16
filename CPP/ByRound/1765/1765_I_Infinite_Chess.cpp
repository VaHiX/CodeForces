// Problem: CF 1765 I - Infinite Chess
// https://codeforces.com/contest/1765/problem/I

/*
 * Problem: Infinite Chess
 * 
 * Description:
 * Find minimum number of moves for a black king to reach target square,
 * avoiding squares attacked by white pieces. White pieces do not move.
 * 
 * Algorithms/Techniques:
 * - BFS with priority queue (Dijkstra's algorithm)
 * - Coordinate compression for efficient handling of infinite board
 * - Piece movement simulation for attack zones
 * 
 * Time Complexity: O((max(10^8, n) * log(max(10^8, n))) * 8 * 3) 
 * Space Complexity: O(max(10^8, n) * 8) 
 */

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <initializer_list>
#include <utility>

using namespace std;
const string al = "KQRBN";
const int INF = 1e9;
struct mv {
  int dx, dy;
};
struct piece {
  int x, y, t;
};
struct seg {
  int l, r;
};
struct pos {
  int x, y;
};
bool operator<(const pos &a, const pos &b) {
  if (a.x != b.x)
    return a.x < b.x;
  return a.y < b.y;
}
// Movement vectors for each piece type
vector<vector<mv>> mvs(
    {{{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}}, // King moves
     {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1}},  // Queen moves
     {{-1, 0}, {0, 1}, {1, 0}, {0, -1}},                                       // Rook moves
     {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}},                                     // Bishop moves
     {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}}}); // Knight moves
int main() {
  int sx, sy, fx, fy;
  cin >> sx >> sy >> fx >> fy;
  swap(sx, sy); // Swap to 0-indexed
  swap(fx, fy);
  --sx;
  --fx;
  int k;
  cin >> k;
  vector<piece> a(k);
  for (int i = 0; i < k; i++) {
    string t;
    cin >> t >> a[i].x >> a[i].y;
    swap(a[i].x, a[i].y); // Swap to 0-indexed
    --a[i].x;
    a[i].t = al.find(t[0]); // Map piece type to index
  }
  sort(a.begin(), a.end(), [](const piece &a, const piece &b) {
    if (a.x != b.x)
      return a.x < b.x;
    return a.y < b.y;
  });
  // Collect Y coordinates for compression
  vector<int> base({sy, fy});
  for (int i = 0; i < k; i++)
    base.push_back(a[i].y);
  vector<int> ys;
  for (int y : base)
    for (int i = y - 16; i <= y + 16; ++i)
      ys.push_back(i);
  sort(ys.begin(), ys.end());
  ys.resize(unique(ys.begin(), ys.end()) - ys.begin());
  
  // Compress Y coordinates to indices
  vector<vector<char>> tk(8, vector<char>(ys.size()));
  for (int i = 0; i < k; i++) {
    a[i].y = lower_bound(ys.begin(), ys.end(), a[i].y) - ys.begin();
    tk[a[i].x][a[i].y] = true;
  }
  sy = lower_bound(ys.begin(), ys.end(), sy) - ys.begin();
  fy = lower_bound(ys.begin(), ys.end(), fy) - ys.begin();
  
  // Mark areas under attack
  vector<vector<char>> bad = tk;
  for (int i = 0; i < k; i++) {
    int x = a[i].x, y = a[i].y;
    if (a[i].t == 0 || a[i].t == 4) {
      // King and Knight moves (one step only)
      for (auto it : mvs[a[i].t]) {
        int nx = x + it.dx;
        int ny = y + it.dy;
        if (0 <= nx && nx < 8)
          bad[nx][ny] = true;
      }
    } else {
      // Queen, Rook, Bishop moves (multiple steps)
      for (auto it : mvs[a[i].t]) {
        for (int nx = x + it.dx, ny = y + it.dy;; nx += it.dx, ny += it.dy) {
          if (nx < 0 || nx >= 8)
            break;
          if (ny < 0 || ny >= int(ys.size()))
            break;
          if (tk[nx][ny])
            break;
          bad[nx][ny] = true;
        }
      }
    }
  }
  
  // Dijkstra's algorithm for shortest path
  vector<vector<int>> d(8, vector<int>(ys.size(), INF));
  vector<vector<pos>> p(8, vector<pos>(ys.size()));
  set<pair<int, pos>> q;
  d[sx][sy] = 0;
  q.insert({0, {sx, sy}});
  
  while (!q.empty()) {
    int x = q.begin()->second.x;
    int y = q.begin()->second.y;
    q.erase(q.begin());
    
    if (x == fx && y == fy) {
      cout << d[x][y] << endl;
      return 0;
    }
    
    // Check all neighbors (including diagonals)
    for (int ny : {y - 1, y, y + 1}) {
      if (ny < 0 || ny >= int(ys.size()))
        continue;
      int dy = max(1, abs(ys[y] - ys[ny]));
      for (int nx = max(0, x - 1); nx <= min(7, x + 1); ++nx)
        if (!bad[nx][ny]) {
          int nd = d[x][y] + dy;
          if (d[nx][ny] > nd) {
            q.erase({d[nx][ny], {nx, ny}});
            d[nx][ny] = nd;
            p[nx][ny] = {x, y};
            q.insert({d[nx][ny], {nx, ny}});
          }
        }
    }
  }
  cout << -1 << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/