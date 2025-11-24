// Problem: CF 1716 C - Robot in a Hallway
// https://codeforces.com/contest/1716/problem/C

/*
 * Problem: Robot in a Hallway
 * 
 * Purpose: Find the minimum time for a robot to visit all cells in a 2xM grid,
 *          starting from (1,1), following constraints on movement and unlock times.
 * 
 * Approach:
 * - Dynamic Programming with backward traversal to compute the earliest time
 *   each cell can be reached while maintaining the path constraint.
 * - Then perform forward traversal to determine minimum time to complete the path.
 * 
 * Time Complexity: O(m) per test case
 * Space Complexity: O(m) for storing DP table and auxiliary arrays
 * 
 * Algorithms / Techniques:
 * - Dynamic Programming (backward and forward pass)
 * - Greedy optimization with max operations
 */

#include <iostream>
#include <algorithm>

using namespace std;

int t, m, a[2][222222], p[2][222222], ans, n;

int main() {
  cin >> t;
  while (t--) {
    cin >> m;
    // Read the grid values
    for (int j = 0; j < 2; j++)
      for (int i = 0; i < m; i++)
        cin >> a[j][i];
    
    // Initialize starting point
    a[0][0] = -1; // Marking starting cell as visited
    
    // Initialize the suffix DP array (p) for both rows
    p[0][m] = 0;
    p[1][m] = 0;
    
    // Backward pass to compute minimum times to reach each cell from the end
    for (int i = m - 1; i >= 0; i--)
      for (int j = 0; j < 2; j++)
        // For each cell (j, i), we compute minimum time to reach it
        // considering:
        // 1. Time to unlock the current cell (a[j][i])
        // 2. Time to unlock the opposite row cell (a[1-j][i])
        // 3. Time to finish the rest of the path (p[j][i+1])
        // This is max of: unlock time + delay to reach, time for opposite row + 2*(steps left), or path continuation
        p[j][i] =
            max(max(a[1 - j][i] + 1, a[j][i] + (m - i) * 2), p[j][i + 1] + 1);
    
    ans = 1111111111; // Initialize with large value
    n = 0;             // Track max time needed to reach current column
    
    // Forward pass to get result
    for (int i = 0; i < m; i++) {
      int c = i & 1; // Determine which row we're on (0 or 1)
      
      // Update answer by comparing current result with the required time to complete path
      ans = min(ans, max(n, p[c][i]));
      
      // Update n with the max time needed to reach either row at column i
      n = max(n, max(a[c][i] + (m - i) * 2, a[1 - c][i] + (m - i) * 2 - 1));
    }
    
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/