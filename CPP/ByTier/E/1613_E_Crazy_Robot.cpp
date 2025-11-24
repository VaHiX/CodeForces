// Problem: CF 1613 E - Crazy Robot
// https://codeforces.com/contest/1613/problem/E

/*
 * Problem: Crazy Robot
 * 
 * Purpose: 
 *   Determine which free cells (marked with '.') in a grid can force a crazy robot to reach the lab (marked with 'L').
 *   The robot moves in a direction different from the command sent, and if there's no valid move, it stays.
 * 
 * Approach:
 *   1. For each cell in the grid, we simulate a backward search from the lab 'L'.
 *   2. A cell is marked as '+' if it's reachable from the lab under the constraint that the robot must always move towards the lab.
 *   3. A cell is considered reachable if it has fewer than 2 free neighbors (i.e., it's a "dead end" or part of a chain leading to lab).
 * 
 * Time Complexity: O(n * m)
 *   - Each cell is visited at most once due to the recursive nature of the solution.
 * 
 * Space Complexity: O(n * m)
 *   - Space to store the grid and recursion stack space in worst case.
 * 
 * Algorithms/Techniques:
 *   - Depth-First Search (DFS) with backtracking
 *   - Grid traversal with boundary checks
 *   - Recursive approach for determining valid escape paths
 */

#include <iostream>
#include <string>
#include <utility>

#define _ int
using namespace std;
string g[_(1e6)]; // Grid storage
_ n, m, t, v, u, i, j;
pair<_, _> d[] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}}; // Directions: right, left, up, down

// Check if a cell is valid and is free ('.')
_ C(_ v, _ u) { return v >= 0 && v < n && u >= 0 && u < m && g[v][u] == '.'; }

// Recursive function to mark reachable cells from lab (backtracking)
void s(_ v, _ u) {
  for (auto [x, y] : d) {
    v += x, u += y;
    _ k = 0;
    // Count how many neighbors of the current cell are free
    for (auto [x2, y2] : d)
      k += C(v + x2, u + y2);
    // If cell is free and has less than 2 free neighbors, mark it as reachable (+)
    if (C(v, u) && k < 2) {
      g[v][u] = '+';
      s(v, u);
    }
    v -= x, u -= y; // Backtrack
  }
}

_ main() {
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (i = 0; i < n; i++) {
      cin >> g[i];
      for (j = 0; j < m; j++)
        if (g[i][j] == 'L')
          v = i, u = j; // Store lab position
    }
    s(v, u); // Start DFS from lab
    for (i = 0; i < n; i++)
      cout << g[i] << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/