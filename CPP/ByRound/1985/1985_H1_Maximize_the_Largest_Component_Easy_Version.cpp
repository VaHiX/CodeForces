// Problem: CF 1985 H1 - Maximize the Largest Component (Easy Version)
// https://codeforces.com/contest/1985/problem/H1

/*
 * Problem: Maximize the Largest Component (Easy Version)
 * Algorithm: 
 *   - Preprocess the grid to count empty cells in each row and column
 *   - For each connected component of '#' cells, simulate the effect of setting
 *     an entire row or column to '#' and calculate how much it increases the
 *     size of the largest connected component.
 *   - Use BFS to find connected components and update the contribution of each
 *     row/column to the final answer.
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for the grid and auxiliary arrays
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
void initial() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}
using ll = long long int;
void run() {
  int n, m, i, j, mau, mad, mar, mal, f;
  cin >> n >> m;
  bool a[n + 2][m + 2]; // Grid with padding
  int b[n + 1], c[m + 1]; // b[i] = number of empty cells in row i, c[j] = number of empty cells in column j
  char t;
  // Read the grid and set padding to 0
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++)
      cin >> t, a[i][j] = (t == '#');
  }
  for (i = 0; i <= n + 1; i++)
    a[i][0] = 0, a[i][m + 1] = 0;
  for (i = 0; i <= m + 1; i++)
    a[0][i] = 0, a[n + 1][i] = 0;
  // Initialize row and column counts
  for (i = 1; i <= n; i++)
    b[i] = 0;
  for (i = 1; i <= m; i++)
    c[i] = 0;
  // Count empty cells in each row
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++)
      b[i] += !a[i][j];
  }
  // Count empty cells in each column
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++)
      c[i] += !a[j][i];
  }
  queue<pair<int, int>> q; // BFS queue
  // Process each connected component of '#' cells
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++) {
      if (!a[i][j]) // Skip if already processed or is '.' 
        continue;
      f = 0; // Size of the connected component
      mau = i; // Min row
      mad = i; // Max row
      mal = j; // Min col
      mar = j; // Max col
      // BFS to find the connected component
      for (q.push(make_pair(i, j)); !q.empty(); q.pop()) {
        if (!a[q.front().first][q.front().second]) // Skip if already processed  
          continue;
        mau = min(mau, q.front().first);
        mad = max(mad, q.front().first);
        mal = min(mal, q.front().second);
        mar = max(mar, q.front().second);
        a[q.front().first][q.front().second] = 0; // Mark as processed
        f++; // Increment size
        // Push neighbors to queue if they are part of the component
        if (a[q.front().first][q.front().second + 1])
          q.push(make_pair(q.front().first, q.front().second + 1));
        if (a[q.front().first][q.front().second - 1])
          q.push(make_pair(q.front().first, q.front().second - 1));
        if (a[q.front().first + 1][q.front().second])
          q.push(make_pair(q.front().first + 1, q.front().second));
        if (a[q.front().first - 1][q.front().second])
          q.push(make_pair(q.front().first - 1, q.front().second));
      }
      // Increment the row and column counts with the size of the component
      mau--; // Adjust for 1-based indexing
      mal--;
      mad++;
      mar++;
      while (mau <= mad)
        b[mau] += f, mau++;
      while (mal <= mar)
        c[mal] += f, mal++;
    }
  }
  // Find the maximum count in rows and columns
  mau = 0;
  for (i = 1; i <= n; i++)
    mau = max(mau, b[i]);
  for (i = 1; i <= m; i++)
    mau = max(mau, c[i]);
  cout << mau << '\n';
}
int main() {
  initial();
  int tt, i, n;
  cin >> tt;
  while (tt--)
    run();
}


// https://github.com/VaHiX/CodeForces/