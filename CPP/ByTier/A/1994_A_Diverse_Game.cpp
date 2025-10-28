// Problem: CF 1994 A - Diverse Game
// https://codeforces.com/contest/1994/problem/A

/*
 * Problem: Diverse Game
 * 
 * Purpose: Given a matrix 'a' containing all integers from 1 to n*m,
 *          construct a matrix 'b' such that b[i][j] != a[i][j] for all i,j.
 *          This is essentially a derangement of the matrix elements.
 * 
 * Algorithm/Technique:
 *   - For a matrix of size n x m, we need to rearrange elements such that
 *     no element appears in its original position.
 *   - If n = 1 and m = 1, it is impossible (only one element, so it must stay at same position).
 *   - For larger matrices:
 *     1. First, perform a cyclic shift of each row to the left (move first element to last).
 *     2. Then, perform a cyclic shift of each column downward (move first element to last).
 *   - This ensures no element stays in its original position.
 * 
 * Time Complexity: O(n * m) - We iterate through the matrix twice for shifting operations.
 * Space Complexity: O(n * m) - We use a fixed-size 2D array to store the matrix.
 */

#include <iostream>

#define int long long
using namespace std;

int a[1008][1008];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++)
        cin >> a[i][j];
    }
    // If matrix is 1x1, no valid arrangement is possible
    if (n == 1 && m == 1) {
      cout << -1 << endl;
      continue;
    }
    // Perform a left cyclic shift on each row
    for (int i = 1; i <= n; i++) {
      int f = a[i][1]; // Store first element of row
      for (int j = 1; j <= m; j++) {
        a[i][j] = a[i][j + 1]; // Shift elements to the left
      }
      a[i][m] = f; // Place first element at the end
    }
    // Perform a downward cyclic shift on each column
    for (int i = 1; i <= m; i++) {
      int f = a[1][i]; // Store first element of column
      for (int j = 1; j <= n; j++) {
        a[j][i] = a[j + 1][i]; // Shift elements downward
      }
      a[n][i] = f; // Place first element at the bottom
    }
    // Output the rearranged matrix
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << a[i][j];
        if (j != m)
          cout << " ";
      }
      cout << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/