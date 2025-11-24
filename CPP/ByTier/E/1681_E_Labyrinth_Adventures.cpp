// Problem: CF 1681 E - Labyrinth Adventures
// https://codeforces.com/contest/1681/problem/E

/*
Code Purpose:
This code solves the problem of finding the shortest path in a layered labyrinth where each layer is connected via doors.
It uses a sparse table (segment tree-like structure) for efficient range minimum queries on distances between layers.
The algorithm pre-processes distances between doors in consecutive layers and then answers queries by combining distances using the sparse table.

Algorithms/Techniques:
- Sparse Table (for range minimum queries)
- Multi-source BFS-style preprocessing
- Coordinate compression and layer-based graph traversal
- Path decomposition using binary lifting technique

Time Complexity: O(n * log(n) + m * log(n))
Space Complexity: O(n * log(n))

Where n is the number of layers, and m is the number of queries.
*/

#include <bits/std_abs.h>
#include <stddef.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

using namespace std;
#define int long long
#define fi first
#define se second
#define F(i, l, r) for (int i = l; i <= r; ++i)
typedef array<array<int, 2>, 2> T;
typedef pair<int, int> PII;
int d(PII x) { return max(x.fi, x.se); }
const int N = 1e5, inf = 1e18;
PII a[N][2];
T f[19][N];
T mul(T x, T y) {
  T z;
  F(i, 0, 1) F(j, 0, 1) z[i][j] = inf;
  F(i, 0, 1) F(j, 0, 1) F(k, 0, 1) z[i][j] = min(z[i][j], x[i][k] + y[k][j]);
  return z;
}
int get(PII x, PII y) { return abs(y.fi - x.fi) + abs(y.se - x.se); }
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);
  int n;
  cin >> n;
  F(i, 1, n - 1) F(j, 0, 1) {
    cin >> a[i][j].fi >> a[i][j].se;
    a[i][j].fi -= j;
    a[i][j].se -= !j;
  }
  F(i, 0, n - 2)
  F(j, 0, 1) F(k, 0, 1) f[0][i][j][k] = get(a[i][j], a[i + 1][k]);
  F(i, 1, 17)
  F(j, 0, n - (1 << i) - 1) f[i][j] =
      mul(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
  int q;
  cin >> q;
  while (q--) {
    PII x, y;
    cin >> x.fi >> x.se >> y.fi >> y.se;
    x.fi--;
    y.fi--;
    x.se--;
    y.se--;
    if (d(x) != d(y)) {
      if (d(x) > d(y))
        swap(x, y);
      T z = T();
      z[0][1] = z[1][0] = inf;
      for (int i = 17, j = d(x) + 1; i >= 0; i--) {
        if (j + (1 << i) <= d(y))
          z = mul(z, f[i][j]), j += 1 << i;
      }
      int ans = inf;
      F(i, 0, 1)
      F(j, 0, 1) ans =
          min(ans, get(x, a[d(x) + 1][i]) + z[i][j] + get(a[d(y)][j], y));
      cout << ans << "\n";
    } else
      cout << get(x, y) << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/