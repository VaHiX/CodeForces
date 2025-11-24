// Problem: CF 1985 H2 - Maximize the Largest Component (Hard Version)
// https://codeforces.com/contest/1985/problem/H2

/*
 * Problem: Maximize the Largest Component (Hard Version)
 * 
 * Algorithm:
 * - Union-Find (Disjoint Set Union) with path compression and union by size
 * - For each '#' in the grid, we compute connected components
 * - Then for each cell in the grid, we calculate how many additional '#' cells
 *   we can add by setting row and column to '#'
 * - The key idea is to precompute for each connected component the bounding box
 *   (min/max row/column), and simulate adding a row and column to the full grid
 *   and compute the new connected component size.
 * 
 * Time Complexity: O(n * m * α(n * m)) where α is the inverse Ackermann function
 * Space Complexity: O(n * m)
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
int n, m;
char s[1000006];
int fa[1000006], sz[1000006];
int Mx[1000006][2][2]; // Mx[i][0] stores row bounds, Mx[i][1] stores column bounds for component i
int fnd(int x) { return fa[x] == x ? x : fa[x] = fnd(fa[x]); }
void qmin(int &x, int y) {
  if (x > y)
    x = y;
}
void qmax(int &x, int y) {
  if (x < y)
    x = y;
}
void cup(int u, int v) {
  if (u == v) {
    return;
  }
  if (sz[u] < sz[v]) {
    swap(u, v);
  }
  fa[v] = u;
  sz[u] += sz[v];
  for (int i = 0; i < 2; i++) {
    qmin(Mx[u][i][0], Mx[v][i][0]); // update min of row/column
    qmax(Mx[u][i][1], Mx[v][i][1]); // update max of row/column
  }
}
int cnt[1000006], r[1000006], c[1000006];
void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> s + i *m;
  }
  memset(r, 0, n << 2);
  memset(c, 0, m << 2);
  memset(cnt, 0, n * m << 2);
  int res = 0;
  for (int i = 0; i < n * m; i++) {
    fa[i] = i;
    if (s[i] == '.') {
      continue;
    }
    r[i / m] += 1;
    c[i % m] += 1;
    sz[i] = 1;
    Mx[i][0][0] = Mx[i][0][1] = i / m;
    Mx[i][1][0] = Mx[i][1][1] = i % m;
    if (Mx[i][0][0])
      Mx[i][0][0] -= 1;
    Mx[i][0][1] += 2;
    if (Mx[i][1][0])
      Mx[i][1][0] -= 1;
    Mx[i][1][1] += 2;
    if (i % m && s[i - 1] == '#') {
      cup(fnd(i), fnd(i - 1));
    }
    if (i >= m && s[i - m] == '#') {
      cup(fnd(i), fnd(i - m));
    }
  }
  for (int i = 0; i < n * m; i++) {
    if (s[i] == '.' || fa[i] != i) {
      continue;
    }
    for (int u = -1; u < 2; u++) {
      int x = u == -1 ? 0 : Mx[i][0][u];
      if (x >= n) {
        continue;
      }
      for (int v = -1; v < 2; v++) {
        int y = v == -1 ? 0 : Mx[i][1][v];
        if (y >= m || u == -1 && v == -1) {
          continue;
        }
        cnt[x * m + y] += ((u + v & 1) ? 1 : -1) * sz[i];
      }
    }
  }
  for (int i = 0; i < n * m; i++) {
    cnt[i] += (i % m ? cnt[i - 1] : 0) + (i >= m ? cnt[i - m] : 0) -
              (i % m && i >= m ? cnt[i - m - 1] : 0);
    res = max(cnt[i] - r[i / m] - c[i % m] + (s[i] == '#') + n + m - 1, res);
  }
  printf("%d\n", res);
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/