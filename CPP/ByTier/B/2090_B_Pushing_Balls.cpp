// Problem: CF 2090 B - Pushing Balls
// https://codeforces.com/contest/2090/problem/B

/*
B. Pushing Balls
Algorithms/Techniques: Simulation with directional propagation logic
Time Complexity: O(n * m) per test case
Space Complexity: O(n * m) for storing the grid and the reachability matrix

The problem simulates pushing balls into an n×m grid from either left or top edges.
Each ball continues moving until it hits another ball or reaches the edge.
We check whether the final state is achievable by:
1. Marking all positions reachable from leftward pushes (row-wise)
2. Marking all positions reachable from upward pushes (column-wise)
3. Ensuring that every '1' in the grid is reachable from at least one direction
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> b(n);
    for (long row = 0; row < n; row++) {
      std::cin >> b[row];
    }
    // Create a matrix to store whether each cell is reachable from either left or top
    std::vector<std::vector<bool>> d(n, std::vector<bool>(m, 0));
    
    // For each row, mark cells as reachable if they are filled with '1'
    // and all previous cells in the same row are also filled (i.e., no '0' before)
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        if (b[row][col] == '0') {
          break;
        }
        d[row][col] = 1;
      }
    }
    
    // For each column, mark cells as reachable if they are filled with '1'
    // and all previous cells in the same column are also filled
    for (long col = 0; col < m; col++) {
      for (long row = 0; row < n; row++) {
        if (b[row][col] == '0') {
          break;
        }
        d[row][col] = 1;
      }
    }
    
    // Check if all '1's in the grid are marked as reachable
    bool res(true);
    for (long row = 0; res && row < n; row++) {
      for (long col = 0; res && col < m; col++) {
        if (b[row][col] == '1' && !d[row][col]) {
          res = false;
        }
      }
    }
    
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/