// Problem: CF 2101 A - Mex in the Grid
// https://codeforces.com/contest/2101/problem/A

/*
 * Problem: Maximize Sum of MEX Over All Subgrids
 * Algorithm: Spiral filling pattern to assign values from 0 to n^2 - 1
 * Time Complexity: O(n^2) per test case
 * Space Complexity: O(n^2) for the grid storage
 *
 * This solution uses a spiral traversal to fill the grid in order,
 * which helps achieve a good distribution of numbers to maximize
 * the sum of MEX values over all subgrids.
 */

#include <iostream>
using namespace std;
const int N = 505;
int a[N][N], dx[]{1, 0, -1, 0}, dy[]{0, 1, 0, -1};

void ATRI() {
  int n;
  cin >> n;
  int x = 1, y = 1, p = n * n, k = 0;
  // Initialize all grid positions with -1
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      a[i][j] = -1;
  // Spiral filling loop
  while (p) {
    a[x][y] = --p;  // Assign the next number in descending order
    // Check if next step is out of bounds or already filled
    if (~a[x + dx[k]][y + dy[k]])  // ~ operator checks if value is not -1
      k = (k + 1) % 4;  // Change direction (right -> down -> left -> up)
    x += dx[k], y += dy[k];  // Move to next cell
  }
  // Output the filled grid
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cout << a[i][j] << " \n"[j == n];  // Print with space or newline
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    ATRI();
  return 0;
}


// https://github.com/VaHiX/codeForces/