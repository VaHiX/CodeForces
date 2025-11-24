// Problem: CF 2160 E - Rectangles
// https://codeforces.com/contest/2160/problem/E

/*
Algorithm: Rectangle Area Minimization
Approach:
- For each pair of rows (i, j) where i < j, find columns k such that both rows i and j have '1'
- For each such pair of columns, compute the area of rectangle (i, j, prev, k) where prev is the previous column with '1' in both rows
- Update the minimum area for all cells within this rectangle
- For each cell (i, j), take minimum over all rectangles that contain it

Time Complexity: O(n^2 * m) where n is number of rows and m is number of columns
Space Complexity: O(n * m) for storing the answer grid

The algorithm works by scanning all pairs of rows and finding valid columns that form rectangles.
It optimizes with a two-pointer approach to avoid rechecking the same intervals.
*/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
vector<vector<int>> solve(vector<vector<bool>> &inp) {
  int n = inp.size(); // Number of rows
  int m = inp[0].size(); // Number of columns
  assert(n <= m); // Ensure n <= m for optimization
  vector<vector<int>> ans(n, vector<int>(m, n * m + 1)); // Initialize with large value
  for (int i = 0; i + 1 < n; ++i) { // For each row i
    for (int j = i + 1; j < n; ++j) { // For each row j > i
      int prev = -1; // Track the previous column in current row pair
      for (int k = 0; k < m; k++) { // Iterate through columns
        if (inp[i][k] && inp[j][k]) { // If both rows have '1' in column k
          if (prev != -1) { // If prev was set, calculate rectangle area
            int newVal = (j - i + 1) * (k - prev + 1); // Area of rectangle from prev to k (inclusive)
            for (int x = prev; x <= k; ++x) { // Update all cells in this rectangle
              ans[j][x] = min(ans[j][x], newVal); // Update minimum area
            }
          }
          prev = k; // Set prev to current column
        }
      }
    }
    for (int k = 0; k < m; ++k) { // After processing all row pairs with row i
      for (int j = i + 1; j < n; ++j) { // Update minimum area for cells in row i from rows below
        ans[i][k] = min(ans[i][k], ans[j][k]);
      }
    }
  }
  for (int i = 0; i < n; ++i) { // Replace large values with 0
    for (int j = 0; j < m; ++j) {
      if (ans[i][j] > n * m)
        ans[i][j] = 0;
    }
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    int n = 500, m = 500;
    cin >> n >> m;
    vector<string> inp(n);
    for (int i = 0; i < n; ++i) {
      cin >> inp[i];
    }
    if (n <= m) {
      vector<vector<bool>> v(n, vector<bool>(m));
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          v[i][j] = inp[i][j] == '1';
        }
      }
      vector<vector<int>> ans = solve(v);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          printf("%d%c", ans[i][j], j + 1 == m ? '\n' : ' ');
        }
      }
    } else {
      vector<vector<bool>> v(m, vector<bool>(n));
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          v[i][j] = inp[j][i] == '1';
        }
      }
      vector<vector<int>> ans = solve(v);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          printf("%d%c", ans[j][i], j + 1 == m ? '\n' : ' ');
        }
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/