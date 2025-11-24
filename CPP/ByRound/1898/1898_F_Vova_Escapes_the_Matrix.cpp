// Problem: CF 1898 F - Vova Escapes the Matrix
// https://codeforces.com/contest/1898/problem/F

/*
 * Problem: F. Vova Escapes the Matrix
 * 
 * Algorithm/Techniques:
 * - Multi-source BFS to compute shortest distances from all exits to every cell
 * - Identify boundary exits and perform BFS from them
 * - For each exit, perform BFS to mark reachable cells and track conflicts
 * - Use BFS to determine maximum number of cells that can be blocked without changing the matrix type
 * 
 * Time Complexity: O(n * m) per test case, as each cell is visited a constant number of times
 * Space Complexity: O(n * m) for storing matrix and BFS queues
 */

#include <stdio.h>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <utility>

#pragma GCC optimize("unroll-loops")
using namespace std;
namespace Fread {
const int SIZE = 1 << 16;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
#define getchar Fread ::getchar
namespace Fastio {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
      c = getchar();
    while (c >= '0' && c <= '9') {
      x = x * 10 + (c - '0');
      c = getchar();
    }
    return *this;
  }
  Reader &operator>>(char &c) {
    c = getchar();
    while (c == '\n' || c == ' ')
      c = getchar();
    return *this;
  }
} cin;
} // namespace Fastio
#define cin Fastio ::cin
#define f first
#define s second
#define endl '\n';
#define pi pair<int, int>
void ckmin(int &a, int &b) {
  if (b < a)
    a = b;
}
const int N = 1e3, INF = 1e7;
pi g[N][N];
int dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};
void solve() {
  int n, m, cnt_o = 0;
  cin >> n >> m;
  char x;
  queue<pi> Q;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      g[i][j].s = -1;
      cin >> x;
      if (x == '#')
        g[i][j].f = 0;
      else if (x == '.')
        g[i][j].f = -1, cnt_o++;
      else
        g[i][j].f = -1, g[i][j].s = 0, Q.push({i, j});
    }
  auto InBounds = [&](int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m;
  };
  while (!Q.empty()) {
    pi t = Q.front();
    int r = t.f, c = t.s;
    Q.pop();
    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i], nc = c + dc[i];
      if (!InBounds(nr, nc) || !g[nr][nc].f || g[nr][nc].s != -1)
        continue;
      g[nr][nc].s = g[r][c].s + 1;
      Q.push({nr, nc});
    }
  }
  int cnt_e = 0, mi_d = INF, id = 1, ans = INF;
  queue<pair<pi, pi>> q;
  auto prep = [&](int i, int j) {
    cnt_e++;
    ckmin(mi_d, g[i][j].s);
    g[i][j].f = id;
    q.push({{i, j}, {id, 0}});
    id++;
  };
  for (int i = 1; i < n; i++)
    for (int j : {0, m - 1})
      if (g[i][j].s != -1)
        prep(i, j);
  for (int i : {0, n - 1})
    for (int j = 1; j < m; j++)
      if (g[i][j].s != -1)
        prep(i, j);
  if (cnt_e == 0) {
    cout << cnt_o << endl;
    return;
  }
  if (cnt_e == 1) {
    cout << cnt_o - mi_d << endl;
    return;
  }
  while (!q.empty()) {
    pair<pi, pi> t = q.front();
    q.pop();
    pi t1 = t.f, t2 = t.s;
    int r = t1.f, c = t1.s, cur = t2.f, di = t2.s;
    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i], nc = c + dc[i];
      if (!InBounds(nr, nc) || !g[nr][nc].f)
        continue;
      if (g[nr][nc].f < 0) {
        g[nr][nc].s += di + 1;
        g[nr][nc].f = cur;
        q.push({{nr, nc}, {cur, di + 1}});
      } else if (g[nr][nc].f != cur) {
        g[nr][nc].s += di + 1;
        ckmin(ans, g[nr][nc].s);
        g[nr][nc].f = 0;
        q.push({{nr, nc}, {cur, di + 1}});
      }
    }
  }
  cout << cnt_o - ans << endl;
}
int main() {
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/