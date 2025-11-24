// Problem: CF 1415 A - Prison Break
// https://codeforces.com/contest/1415/problem/A

/*
Task: Prison Break
Algorithms/Techniques: Mathematical calculation, optimization
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem requires finding the minimum time for all prisoners to reach the escape tunnel at (r, c).
Each prisoner can move to adjacent cells in 1 second. The minimum time is the maximum Manhattan distance
from any cell to the tunnel, which is calculated as the maximum of:
- Distance from prisoner's row to tunnel's row
- Distance from prisoner's column to tunnel's column

Since the prison grid is n x m, and we're measuring the max distance from any point in the grid to (r, c),
we can calculate it directly using distances from edges.
For a cell at row a and column b:
- Distance to top edge = a - 1
- Distance to bottom edge = n - a
- Distance to left edge = b - 1
- Distance to right edge = m - b

The minimum time is max(a - 1, n - a) + max(b - 1, m - b)
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int n, m, a, b, T;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    cout << max(a - 1, n - a) + max(b - 1, m - b) << "\n"; // Calculate minimum time
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/