// Problem: CF 1360 E - Polygon
// https://codeforces.com/contest/1360/problem/E

/*
 * Problem: Polygon
 * 
 * Purpose: Determine if a given binary matrix can be produced by firing cannons
 *          from the top and left edges of a square grid. Each cannon shoots a '1'
 *          that travels in a straight line until it hits a boundary or another '1'.
 * 
 * Algorithm:
 * - For each cell containing '1', check if it has a neighboring '1' either below or to the right.
 * - If a '1' exists at (row, col) but both (row+1, col) and (col+1, row) are '0', then the
 *   current '1' cannot be a result of any valid cannon shot sequence, because it cannot be
 *   reached by any cannon without an intervening '1'.
 * 
 * Time Complexity: O(n^2) per test case where n is the side length of the matrix.
 * Space Complexity: O(n^2) for storing the matrix.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::string> m(n);
    for (long p = 0; p < n; p++) {
      std::cin >> m[p];
    }
    bool possible(true);
    for (long row = 0; row + 1 < m.size(); row++) {
      for (long col = 0; col + 1 < m[0].size(); col++) {
        if (m[row][col] == '0') {
          continue;
        }
        // Check if the '1' at (row, col) can be reached by a cannon shot
        // If neither the cell below nor to the right is '1', then this '1' 
        // cannot be the result of any valid sequence (no cannon can shoot it without interference)
        if (m[row + 1][col] == '0' && m[row][col + 1] == '0') {
          possible = false;
          break;
        }
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/