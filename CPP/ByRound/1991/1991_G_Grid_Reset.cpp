// Problem: CF 1991 G - Grid Reset
// https://codeforces.com/contest/1991/problem/G

/*
Purpose: Solve the Grid Reset problem where operations (horizontal or vertical) are applied to a grid, 
         and when entire rows or columns become black, they are reset to white. 
         The challenge is to find valid rectangle positions for each operation to avoid conflicts.

Algorithms/Techniques: 
- Simulation-based approach with tracking of row/column reset conditions.
- Adaptive positioning of rectangles to prevent full rows/columns from becoming black.

Time Complexity: O(q * n * m) for each test case, due to potential repeated checks for reset conditions.
Space Complexity: O(n * m) for storing grid and auxiliary arrays.

*/
#include <string.h>
#include <iostream>

using namespace std;
#define N 105
int n, m, k, q, a[N][N], vh[N], vw[N];
void print() {
  for (int i = 1; i <= n; i++)
    vh[i] = 0;
  for (int i = 1; i <= m; ++i)
    vw[i] = 0;
  for (int i = 1; i <= n; i++) {
    int tag = 1;
    for (int j = 1; j <= m; j++)
      tag &= a[i][j];
    vh[i] = tag;
  }
  for (int j = 1; j <= m; j++) {
    int tag = 1;
    for (int i = 1; i <= n; i++)
      tag &= a[i][j];
    vw[j] = tag;
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      a[i][j] -= (vh[i] | vw[j]);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      cout << a[i][j] << " ";
    cout << "\n";
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> m >> k >> q;
    memset(a, 0, sizeof a);
    int nnow = k, mnow = k, npos = 0, mpos = 0, nowpos = 0, typ = 0, deln = 0,
        delm = 0, tagn = 0, tagm = 0;
    while (q--) {
      char c;
      cin >> c;
      if (c == 'H') {
        if (m == k) {
          cout << n << " 1\n";
          continue;
        }
        if (nnow < n - 1) {
          ++nnow;
          cout << nnow << " 1\n";
          continue;
        }
        if (nnow == n - 1) {
          ++nnow;
          cout << nnow << " 1\n";
          tagn = 1;
          npos = 0;
          if (typ == 2) {
            typ = 0;
            npos = nowpos;
            nowpos = 0;
          }
          continue;
        }
        if (tagm) {
          ++mpos;
          cout << mpos << " 1\n";
          if (mpos == k) {
            mpos = 0;
            tagm = 0;
            nowpos = 0;
            mnow = k;
          }
          continue;
        }
        typ = 1;
        ++nowpos;
        cout << nowpos << " 1\n";
        if (nowpos == k) {
          nnow = k;
          typ = 0;
          tagn = 0;
          nowpos = npos;
          if (nowpos)
            typ = 2;
        }
        continue;
      }
      if (n == k) {
        cout << "1 " << m << "\n";
        continue;
      }
      if (mnow < m - 1) {
        ++mnow;
        cout << 1 << " " << mnow << "\n";
        continue;
      }
      if (mnow == m - 1) {
        ++mnow;
        cout << "1 " << mnow << "\n";
        tagm = 1;
        mpos = 0;
        if (typ == 1)
          typ = 0, mpos = nowpos, nowpos = 0;
        continue;
      }
      if (tagn) {
        ++npos;
        cout << "1 " << npos << "\n";
        if (npos == k)
          npos = 0, nnow = k, tagn = 0, nowpos = 0;
        continue;
      }
      typ = 2;
      ++nowpos;
      cout << "1 " << nowpos << "\n";
      if (nowpos == k) {
        nowpos = mpos;
        mnow = k;
        tagm = 0;
        typ = 0;
        if (nowpos)
          typ = 1;
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/