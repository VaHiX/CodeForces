// Problem: CF 690 B1 - Recover Polygon (easy)
// https://codeforces.com/contest/690/problem/B1

/*
 * Problem: Recover Polygon (easy)
 * 
 * Purpose: Determine if a given contamination grid could be produced by a single 
 * non-zero area rectangular lair with axis-parallel sides on a lattice.
 * 
 * Algorithm:
 * - For each cell with contamination level > 0, check its four corner neighbors.
 * - Count how many of those neighbors have contamination level > 0.
 * - If the count does not match the current cell's contamination level, return "No".
 * - If all cells pass the test, return "Yes".
 * 
 * Time Complexity: O(N^2) where N is the size of the grid.
 * Space Complexity: O(N^2) for storing the grid.
 * 
 * Techniques:
 * - Brute force over all cells.
 * - Neighbor checking using dx/dy arrays.
 * 
 */

#include <stddef.h>
#include <iostream>
#include <string>
#include <vector>

#define fast_cin()                                                             \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
using namespace std;

void solve() {
  long long int n, cnt = 0;
  cin >> n;
  vector<string> vs(n + 2); // Extra space for boundary padding
  string op = "Yes";
  long long int dx[] = {1, 1, -1, -1}, dy[] = {1, -1, 1, -1}; // Directions to check corners
  for (long long int i = 1; i <= n; i++) {
    cin >> vs[i];
    vs[i] = " " + vs[i]; // Add padding to simplify indexing
  }
  for (long long int i = 1; i <= n; i++) {
    for (long long int j = 1; j <= n; j++) {
      if (vs[i][j] - '0') { // If current cell has contamination > 0
        cnt = 0;
        for (long long int k = 0; k < 4; k++) {
          // Check 4 corners around current cell
          cnt += (vs[i + dx[k]][j + dy[k]] - '0' > 0);
        }
        if (cnt != vs[i][j] - '0') { // Compare with expected count
          op = "No";
          cout << op;
          return;
        }
      }
    }
  }
  cout << op;
}

int main() {
  fast_cin();
  long long int t;
  t = 1;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/