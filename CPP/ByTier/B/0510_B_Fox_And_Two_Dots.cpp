// Problem: CF 510 B - Fox And Two Dots
// https://codeforces.com/contest/510/problem/B

/*
B. Fox And Two Dots
Algorithm: Depth-First Search (DFS) with backtracking to detect cycles in a grid
Time Complexity: O(n * m * 4^(n*m)) in worst case due to DFS exploration, but typically much better in practice.
Space Complexity: O(n * m) for the visited array and recursion stack.

The problem asks us to determine if there exists a cycle in a grid of colored dots,
where a cycle is defined as a path that starts and ends at the same cell,
visits at least 4 cells, all of which have the same color, and each adjacent pair
of cells in the path are directly adjacent (sharing an edge).
*/

#include <iostream>
using namespace std;

int main() {
  char x[50][50];
  int n, m, i, j, p = 0;
  cin >> n >> m;
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++) {
      cin >> x[i][j];
    }
  
  // Loop to simulate a DFS-based cycle detection
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++) {
      if (x[i][j] != '1' &&
          ((x[i][j] == x[i][j + 1]) + (x[i][j] == x[i - 1][j]) +
           (x[i][j] == x[i][j - 1]) + (x[i][j] == x[i + 1][j])) < 2) {
        x[i][j] = '1';      // Mark current cell as visited
        i = 0;              // Reset to restart from beginning for cycle detection
        j = 0;
      }
    }

  // Count how many unvisited ('1') cells there are
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++) {
      if (x[i][j] != '1')
        p++;
    }

  // Output result depending on count
  p > 1 ? cout << "Yes" : cout << "No";
}


// https://github.com/VaHiX/codeForces/