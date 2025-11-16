// Problem: CF 1028 A - Find Square
// https://codeforces.com/contest/1028/problem/A

/*
Problem: Find the center of a black square painted inside a white grid.
Algorithm: Scan the grid to find the bounding box of all black cells, then compute the center of that box.
Time Complexity: O(n * m), where n is number of rows and m is number of columns.
Space Complexity: O(n * m) for storing the grid.

Input:
- n rows and m columns
- Each cell is either 'W' (white) or 'B' (black)
Output:
- Center coordinates (row, column) of the black square

Techniques:
- Bounding box calculation
- Center computation from min/max coordinates
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::vector<std::string> t(n);
  for (long row = 0; row < n; row++) {
    std::cin >> t[row];
  }
  long top(-1), bottom(-1), left(-1), right(-1);
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      if (t[row][col] == 'W') {
        continue;
      }
      // Update top boundary if not set yet
      if (top <= 0) {
        top = row;
      }
      // Update left boundary if not set yet
      if (left <= 0) {
        left = col;
      }
      // Update bottom boundary
      bottom = (bottom > row) ? bottom : row;
      // Update right boundary
      right = (right > col) ? right : col;
    }
  }
  // Compute center coordinates
  long crow = 1 + (bottom + top) / 2;
  long ccol = 1 + (left + right) / 2;
  std::cout << crow << " " << ccol << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/