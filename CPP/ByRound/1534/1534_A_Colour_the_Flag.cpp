// Problem: CF 1534 A - Colour the Flag
// https://codeforces.com/contest/1534/problem/A

/*
 * Problem: A. Colour the Flag
 * Purpose: Given an n×m grid with 'R', 'W', and '.' characters, color the blank ('.') cells 
 *          such that no two adjacent cells have the same color, and existing colors are preserved.
 *          Adjacent means sharing an edge (not corner).
 *
 * Algorithm:
 *   - Try to color the grid in two possible ways based on a checkerboard pattern:
 *     1. Starting with 'R' at (0,0) => all cells (i+j)%2 == 0 get 'R'
 *     2. Starting with 'W' at (0,0) => all cells (i+j)%2 == 0 get 'W'
 *   - For each pattern, validate if the current grid can support it.
 *   - If valid for either case, output the result.
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for storing the grid and result
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long nr, nc;
    std::cin >> nr >> nc;
    std::vector<std::string> m(nr); // Read input grid
    for (long p = 0; p < nr; p++) {
      std::cin >> m[p];
    }
    bool done(false);
    std::vector<std::string> ret = m; // Copy input to result grid
    for (int w = 0; !done && w <= 1; w++) { // Try both patterns starting with 'R' or 'W'
      bool possible(true);
      for (long row = 0; possible && row < nr; row++) {
        for (long col = 0; possible && col < nc; col++) {
          int par = (row + col) % 2; // Determine expected color based on position parity
          ret[row][col] = (par == w ? 'R' : 'W'); // Assign color depending on pattern
          if (m[row][col] == '.') {
            continue; // Skip blank cells
          }
          if (ret[row][col] != m[row][col]) {
            possible = false; // Conflict with existing cell
          }
        }
      }
      if (possible) {
        done = true; // Valid pattern found
        break;
      }
    }
    if (done) {
      std::cout << "YES" << std::endl;
      for (long row = 0; row < nr; row++) {
        std::cout << ret[row] << std::endl;
      }
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/