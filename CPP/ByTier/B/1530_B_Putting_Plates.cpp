// Problem: CF 1530 B - Putting Plates
// https://codeforces.com/contest/1530/problem/B

/*
Algorithm/Techniques: Greedy placement on edges with checkerboard pattern.
Time Complexity: O(h * w) per test case, where h and w are the dimensions of the table.
Space Complexity: O(1) excluding the output storage.

The approach is to place plates on the edges of the table in a way that avoids
adjacent plates (including diagonally). We use a greedy method:
- For the first and last rows, we place plates in alternating positions (checkerboard).
- For the first and last columns, we place plates in alternating positions.
- Special care is taken to avoid overlaps and ensure no two plates are adjacent.
This greedy strategy ensures maximum number of plates are placed.
*/
#include <iostream>
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    for (long row = 1; row <= n; row++) {
      for (long col = 1; col <= m; col++) {
        // Check if current cell can place a plate:
        // 1. If it's on the first or last row, and column is odd and within bounds
        // 2. If it's on the first or last column, and row is odd and within bounds
        // 3. Special case: last column with odd row (to avoid double counting)
        if ((row == 1 || row == n) && (col & 1) && col + 2 <= m ||
            (row & 1) && (col == 1 || col == m) && row + 2 <= n ||
            col == m && row & 1) {
          std::cout << 1;
        } else {
          std::cout << 0;
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/