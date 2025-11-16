// Problem: CF 1627 A - Not Shading
// https://codeforces.com/contest/1627/problem/A

/*
 * Problem: Make a specific cell (r, c) black using minimum operations.
 * Algorithm: Greedy approach.
 * - If the target cell (r,c) is already black, return 0.
 * - Otherwise, check if there's any black cell in the same row or column as (r,c).
 *   - If yes, we can make that row/column all black in one operation.
 *   - If no such black cell exists, it's impossible.
 * - If there's a black cell in the same row OR column:
 *   - If we have a black cell at (r,c) already, return 0 (already done).
 *   - If there's a black cell in same row or column, we can do 1 operation.
 *   - In most cases, we need 2 operations if no black cell is on the same row or column.
 *
 * Time Complexity: O(n * m) per test case where n is rows and m is columns
 * Space Complexity: O(1) additional space (excluding input storage)
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m, r, c;
    std::cin >> n >> m >> r >> c;
    --r; // Convert to 0-based indexing
    --c;
    bool possible(false);
    long res(2); // Initialize result to maximum possible operations
    
    for (long row = 0; row < n; row++) {
      std::string s;
      std::cin >> s;
      for (long col = 0; col < s.size(); col++) {
        if (s[col] == 'W') {
          continue; // Skip white cells
        }
        possible = true; // At least one black cell found
        
        if (row == r && col == c) {
          res = 0; // Target cell is already black
        }
        if (row == r || col == c) {
          res = (res < 1) ? res : 1; // If on same row or column, only 1 op needed
        }
      }
    }
    
    if (!possible) {
      std::cout << (-1) << std::endl; // No black cell found anywhere
    } else {
      std::cout << res << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/