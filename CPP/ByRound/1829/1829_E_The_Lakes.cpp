// Problem: CF 1829 E - The Lakes
// https://codeforces.com/contest/1829/problem/E

/*
E. The Lakes
Algorithm: Depth-First Search (DFS) on a grid to find connected components of non-zero values,
           where each component represents a lake. For each unvisited cell with value > 0,
           perform DFS to calculate the total volume of that lake and track maximum.

Time Complexity: O(n * m) per test case, since each cell is visited at most once across all searches.
Space Complexity: O(n * m) for the grid storage and recursion stack in worst case (full recursion depth).

*/

#include <cstdio>
#include <vector>
long dfs(long row, long col, std::vector<std::vector<long>> &md) {
  // Base case: out of bounds or water level is 0 (not part of a lake)
  if (row < 0 || row >= md.size() || col < 0 || col >= md[0].size()) {
    return 0;
  }
  if (!md[row][col]) {
    return 0;
  }
  // Store current cell's depth
  long mv = md[row][col];
  // Mark as visited by setting to 0
  md[row][col] = 0;
  // Recursive DFS in all 4 directions (up, down, left, right)
  long ms = mv + dfs(row - 1, col, md) + dfs(row + 1, col, md) +
            dfs(row, col - 1, md) + dfs(row, col + 1, md);
  return ms;
}
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long nr, nc;
    scanf("%ld %ld", &nr, &nc);
    // Initialize grid with zeros
    std::vector<std::vector<long>> d(nr, std::vector<long>(nc, 0));
    // Read input values into grid
    for (long row = 0; row < nr; row++) {
      for (long col = 0; col < nc; col++) {
        scanf("%ld", &d[row][col]);
      }
    }
    long mxd(0);
    // Iterate through each cell to find lakes
    for (long row = 0; row < nr; row++) {
      for (long col = 0; col < nc; col++) {
        long cs = dfs(row, col, d);  // Calculate volume of lake starting at (row,col)
        mxd = (mxd > cs ? mxd : cs); // Keep track of maximum
      }
    }
    printf("%ld\n", mxd);
  }
}


// https://github.com/VaHiX/codeForces/