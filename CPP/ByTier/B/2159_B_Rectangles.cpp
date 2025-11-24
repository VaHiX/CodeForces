// Problem: CF 2159 B - Rectangles
// https://codeforces.com/contest/2159/problem/B

/*
B. Rectangles
Algorithms/Techniques: Dynamic Programming, Rectangle Enumeration

Time Complexity: O(n^2 * m) per test case
Space Complexity: O(n * m) for the grid and auxiliary arrays

The code processes a binary grid of size n x m to find, for each cell (i,j),
the minimum area of any rectangle that contains (i,j) and has all four corners as 1s.
The approach involves:
1. Enumerating all possible rectangles in the grid by fixing top-left and bottom-right corners.
2. For each such valid rectangle, update the minimum area for all cells inside it.
3. The result is stored in a 2D array where ans[i][j] contains the minimum area
   of a rectangle covering cell (i,j), or 0 if no such rectangle exists.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
const int M = 1e9;
vector<vector<int>> a;
vector<vector<int>> ans;
vector<int> v;
int main() {
  int T, n, m, i, j, k;
  bool p;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    p = n > m;
    if (p)
      swap(n, m);
    a.clear();
    ans.clear();
    a.resize(n);
    ans.resize(n);
    for (i = 0; i < n; i++) {
      a[i].resize(m);
      ans[i].resize(m, M);
    }
    if (p)
      swap(n, m);
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
        if (p)
          scanf("%1d", &a[j][i]);
        else
          scanf("%1d", &a[i][j]);
      }
    }
    if (p)
      swap(n, m);
    v.resize(m);
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++)
        v[j] = M;
      for (j = n - 1; j > i; j--) {
        int l = 0, r;
        for (; l < m; l++) {
          if (a[i][l] && a[j][l])
            break;
        }
        r = l;
        while (r < m) {
          for (r++; r < m; r++) {
            if (a[i][r] && a[j][r])
              break;
          }
          if (r >= m)
            break;
          for (k = l; k <= r; k++) {
            v[k] = min(v[k], (r - l + 1) * (j - i + 1));
          }
          l = r;
        }
        for (k = 0; k < m; k++)
          ans[j][k] = min(ans[j][k], v[k]);
      }
      for (k = 0; k < m; k++)
        ans[i][k] = min(ans[i][k], v[k]);
    }
    for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
        ans[i][j] %= M;
    if (p)
      swap(n, m);
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
        if (p)
          printf("%d ", ans[j][i]);
        else
          printf("%d ", ans[i][j]);
      }
      printf("\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/