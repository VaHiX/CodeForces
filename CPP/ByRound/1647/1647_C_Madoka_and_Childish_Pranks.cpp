// Problem: CF 1647 C - Madoka and Childish Pranks
// https://codeforces.com/contest/1647/problem/C

#include <iostream>
#include <vector>
#include <string>

/*
 * Code Purpose:
 * This program solves the problem of determining whether a given binary matrix
 * can be constructed by applying a series of "chess coloring" operations on 
 * subrectangles of the matrix. Each operation starts from a top-left corner and 
 * fills a rectangle with a chessboard pattern where the top-left cell is '0'.
 * 
 * Algorithm:
 * - Key observation: if the top-left cell (0,0) of the desired image is '1',
 *   it's impossible since chess coloring always starts with '0'.
 * - For each cell that is '1', we must perform a chess coloring operation
 *   that includes that cell. We process from bottom-right to top-left.
 * - For each '1' at position (row, col), we create an operation:
 *   - If row > 0, we use a 1x1 operation at (row, col).
 *   - If row == 0, we use a 1x1 operation at (row+1, col).
 * 
 * Time Complexity: O(n * m)
 * Space Complexity: O(n * m)
 */

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> v(n);
    for (long row = 0; row < n; row++) {
      std::cin >> v[row];
    }
    // If the top-left cell is 1, it's impossible to create it with chess coloring
    if (v[0][0] == '1') {
      std::cout << "-1" << std::endl;
      continue;
    }
    std::vector<std::vector<long>> w; // Stores the operations
    // Process from right to left, bottom to top
    for (long col = m - 1; col >= 0; col--) {
      for (long row = n - 1; row >= 0; row--) {
        // If current cell is '0', skip
        if (v[row][col] == '0') {
          continue;
        }
        std::vector<long> b(4);
        // If we are not on the first row, apply 1x1 operation at (row, col)
        if (row) {
          b[0] = row;      // top row
          b[1] = col + 1;  // left column (1-indexed)
          b[2] = row + 1;  // bottom row
          b[3] = col + 1;  // right column
        } else {
          // Special case for first row: apply operation at (row+1, col)
          b[0] = row + 1;  // top row
          b[1] = col;      // left column (1-indexed)
          b[2] = row + 1;  // bottom row
          b[3] = col + 1;  // right column
        }
        w.push_back(b);
      }
    }
    // Output the number of operations
    std::cout << w.size() << std::endl;
    // Output each operation
    for (long p = 0; p < w.size(); p++) {
      std::cout << w[p][0] << " " << w[p][1] << " " << w[p][2] << " " << w[p][3]
                << " " << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/