// Problem: CF 1991 I - Grid Game
// https://codeforces.com/contest/1991/problem/I

/*
Algorithm/Technique: 
The solution uses a strategic approach to fill the grid in a way that ensures the player can always select cells with smaller numbers than the interactor, based on a pre-defined pattern. The key idea involves:
1. Dividing the grid into specific regions (using T() and I() functions) to assign values strategically.
2. Using a game tree approach where the interactor plays optimally, but the player can control selection order by assigning high value cells to interactor and low value cells to player.
3. The algorithm defines a deterministic strategy that works for different grid sizes.

Time Complexity: O(n*m) - The algorithm fills the grid by visiting each cell a constant number of times and performs a constant number of operations per cell.
Space Complexity: O(n*m) - The space used for storing the grid state and auxiliary arrays to track selections.
*/

#include <string.h>
#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
struct poi {
  int x, y;
};
vector<poi> g[105];
int n, m, a[15][15], b[15][15], rv, lv, q;
bool vis[15][15];
void I(int x, int y, char op = 'D') {
  ++q, b[x][y] = q, a[x][y] = rv--;
  g[q].push_back({x, y});
  (op == 'R') ? ++y : ++x;
  b[x][y] = q, a[x][y] = rv--;
  g[q].push_back({x, y});
}
void T(int x, int y) {
  ++q, b[x][y] = q, a[x][y] = lv--;
  g[q].push_back({x, y});
  for (int d : {0, 1, 2, 3}) {
    int i = x + dx[d], j = y + dy[d];
    if (1 <= i && i <= n && 1 <= j && j <= m) {
      b[i][j] = q, a[i][j] = rv--;
      g[q].push_back({i, j});
    }
  }
}
void solve() {
  cin >> n >> m;
  if (n % 2 == 1 && m % 2 == 1) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j)
        cout << (i - 1) * m + j << " ";
      cout << endl;
    }
    set<array<int, 2>> Q;
    for (int o = 1; o <= n * m; ++o) {
      int x, y;
      if (o & 1)
        cin >> x >> y;
      else {
        x = (*Q.begin())[0], y = (*Q.begin())[1];
        cout << x << " " << y << endl;
      }
      vis[x][y] = true, Q.erase({x, y});
      for (int d : {0, 1, 2, 3}) {
        int i = x + dx[d], j = y + dy[d];
        if (1 <= i && i <= n && 1 <= j && j <= m && !vis[i][j])
          Q.insert({i, j});
      }
    }
    return;
  }
  lv = 4, rv = n * m;
  if (m == 4) {
    T(1, 2), T(2, 4);
    if (n % 2 == 0) {
      T(n - 1, 1), T(n, 3);
      for (int i = 2; i <= n - 3; i += 2)
        I(i, 1);
      for (int i = 3; i <= n - 2; i += 2)
        I(i, 2), I(i, 3);
      for (int i = 4; i <= n - 1; i += 2)
        I(i, 4);
    } else {
      T(3, 1), T(n, 2);
      for (int i = 5; i <= n - 1; i += 2)
        I(i, 1);
      for (int i = 4; i <= n - 2; i += 2)
        I(i, 2);
      for (int i = 3; i <= n - 1; i += 2)
        I(i, 3);
      for (int i = 4; i <= n; i += 2)
        I(i, 4);
    }
  } else if (m == 5) {
    T(2, 1), T(1, 3), T(2, 5);
    T(n, 2), I(n - 1, 3, 'R'), I(n, 4, 'R');
    for (int i = 4; i <= n - 1; i += 2)
      I(i, 1), I(i, 5);
    for (int i = 3; i <= n - 2; i += 2)
      I(i, 2), I(i, 3), I(i, 4);
  } else {
    T(1, 2), T(1, m - 1), T(3, 1), T(3, m);
    if (m % 2 == 1) {
      I(1, 4), I(2, 3), I(2, 5), I(3, 4);
      I(4, 2, 'R'), I(4, 5, 'R');
      for (int i = 5; i <= m - 3; i += 2)
        I(1, i, 'R');
      for (int i = 6; i <= m - 2; i += 2)
        I(2, i, 'R'), I(3, i, 'R');
      for (int i = 7; i <= m - 1; i += 2)
        I(4, i, 'R');
    } else {
      for (int i = 4; i <= m - 3; i += 2)
        I(1, i, 'R');
      for (int i = 3; i <= m - 2; i += 2)
        I(2, i, 'R'), I(3, i, 'R');
      for (int i = 2; i <= m - 1; i += 2)
        I(4, i, 'R');
    }
    if (m % 2 == 0) {
      for (int i = 5; i <= n; ++i)
        for (int j = 1; j <= m; j += 2)
          I(i, j, 'R');
    } else {
      for (int i = 5; i <= n; i += 2)
        for (int j = 1; j <= m; ++j)
          I(i, j);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j)
      cout << a[i][j] << " ";
    cout << endl;
  }
  for (int i = 1; i <= q; ++i) {
    sort(g[i].begin(), g[i].end(),
         [&](auto u, auto v) { return a[u.x][u.y] < a[v.x][v.y]; });
  }
  for (int o = 1, x, y; o <= n * m; ++o) {
    if (o & 1) {
      cin >> x >> y, vis[x][y] = true;
      continue;
    } else {
      for (auto z : g[b[x][y]])
        if (!vis[z.x][z.y]) {
          vis[z.x][z.y] = true, cout << z.x << " " << z.y << endl;
          break;
        }
    }
  }
}
signed main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
    memset(vis, 0, sizeof(vis));
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= q; ++i)
      g[i].clear();
    lv = rv = q = 0;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/