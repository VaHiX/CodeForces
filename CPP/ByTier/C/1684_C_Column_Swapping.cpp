// Problem: CF 1684 C - Column Swapping
// https://codeforces.com/contest/1684/problem/C

/*
Algorithm/Techniques: Column-swapping to make rows non-decreasing
Time Complexity: O(n * m) - We process each element in the grid a constant number of times.
Space Complexity: O(n * m) - We store the grid in a 2D array of size (n+1) x (m+1) to allow 1-based indexing.

This solution identifies two columns that, when swapped, can make the grid "good" (each row sorted).
It works by:
1. Finding the first violation of non-decreasing order in each row.
2. Tracking the first and last such violations to determine which columns to swap.
3. After swapping, validating that the grid is now good.
*/

#include <iostream>
#include <utility>

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  int a[n + 1][m + 1];  // 1-based indexing
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];
  
  int x, y;
  x = y = 0;  // x and y will store the indices of columns to swap
  
  // Traverse each row to find violations of non-decreasing order
  for (int i = 1; i <= n; i++) {
    int l = 1;  // l keeps track of the last valid position in current row
    for (int j = 2; j <= m; j++) {
      // If current element is less than the previous one (violation)
      if (a[i][j] < a[i][l]) {
        if (!x)  // First violation found
          x = l;
        y = j;   // Update the second column index
      }
      // If current element is greater than previous, update l to current position
      if (a[i][j] > a[i][j - 1])
        l = j;
    }
  }
  
  // If no violations found, grid is already good. Swap any column with itself
  if (!x)
    x = y = 1;
  
  // Perform the swap on the grid
  for (int i = 1; i <= n; i++)
    swap(a[i][x], a[i][y]);
  
  // Validate if the grid is now good
  for (int i = 1; i <= n; i++) {
    for (int j = 2; j <= m; j++)
      if (a[i][j] < a[i][j - 1]) {
        cout << -1 << '\n';
        return;
      }
  }
  
  // Output the columns swapped
  cout << x << ' ' << y << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/