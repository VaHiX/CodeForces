// Problem: CF 1986 F - Non-academic Problem
// https://codeforces.com/contest/1986/problem/F

/*
 * Problem: Minimize the number of pairs of vertices that are reachable from each other
 * after removing exactly one edge in a connected undirected graph.
 * 
 * Approach:
 * - Use Tarjan's algorithm to find articulation points and bridges.
 * - For each bridge (an edge whose removal increases the number of connected components),
 *   determine the size of the two parts formed after removal.
 * - The maximum number of pairs that can become unreachable by removing a single edge
 *   corresponds to the largest product of component sizes when a bridge is removed.
 * - Final answer is total possible pairs minus the maximum such product.
 *
 * Time Complexity: O(n + m) per test case, where n is vertices and m is edges.
 * Space Complexity: O(n + m) for storing the graph and auxiliary arrays.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define int long long
#define Ciallo main
using namespace std;
const int N = 4e6;
inline int read() {
  int _x = 0, _w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      _w = -1;
#ifdef __linux__
    ch = (char)getchar_unlocked();
#else
    ch = (char)_getchar_nolock();
#endif
  }
  while (ch >= '0' && ch <= '9') {
    _x = (_x << 3) + (_x << 1) + (ch - '0');
#ifdef __linux__
    ch = (char)getchar_unlocked();
#else
    ch = (char)_getchar_nolock();
#endif
  }
  return _x * _w;
}
inline void write(int _x) {
  if (_x < 0) {
#ifdef __linux__
    putchar_unlocked('-');
#else
    _putchar_nolock('-');
#endif
    _x = -_x;
  }
  static int _sta[130];
  int _top = 0;
  do {
    _sta[_top++] = _x % 10, _x /= 10;
  } while (_x);
  while (_top)
#ifdef __linux__
    putchar_unlocked(_sta[--_top] + 48);
  putchar_unlocked('\n');
#else
    _putchar_nolock(_sta[--_top] + 48);
  _putchar_nolock('\n');
#endif
}
int T, n, m, xx, yy;
int e[N], h[N], ne[N], idx;
int low[N], dfn[N], tot, Size[N];
int cnt;
inline void add(int _a, int _b) { e[idx] = _b, ne[idx] = h[_a], h[_a] = idx++; }
void tarjan(int u, int in) {
  Size[u] = 1;
  dfn[u] = low[u] = ++tot;
  for (int i = h[u]; i != -1; i = ne[i]) {
    int j = e[i];
    if (dfn[j] == 0) {
      tarjan(j, i);
      Size[u] += Size[j];
      if (dfn[u] < low[j])
        cnt = max(cnt, Size[j] * (n - Size[j])); // Update max product of component sizes
      low[u] = min(low[u], low[j]);
    } else if (i != (in ^ 1))
      low[u] = min(low[u], dfn[j]);
  }
}
inline void solve() {
  for (int i = 1; i <= n; i++)
    h[i] = -1, dfn[i] = low[i] = 0;
  idx = cnt = tot = 0;
  n = read(), m = read();
  while (m--) {
    xx = read(), yy = read();
    add(xx, yy), add(yy, xx);
  }
  tarjan(1, 0);
  write(n * (n - 1) / 2 - cnt); // Total pairs minus max disconnected pairs
}
signed Ciallo() {
  T = read();
  memset(h, -1, sizeof h);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/