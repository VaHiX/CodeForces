// Problem: CF 1742 C - Stripes
// https://codeforces.com/contest/1742/problem/C

/*
C. Stripes
Purpose: Determine which color (red or blue) was used last to paint an 8x8 grid,
         given that horizontal red rows and vertical blue columns are painted sequentially.
Algorithms/Techniques:
    - Scan entire grid row by row to check if any row is all 'R'
    - Scan entire grid column by column to check if any column is all 'B'
    - The last color painted is the one whose stripe (row or column) exists in the final grid.

Time Complexity: O(N^2) where N = 8, so effectively O(1).
Space Complexity: O(N^2) for storing the grid, so effectively O(1).

Input:
    t test cases, each with 8x8 grid of 'R', 'B', or '.' characters.
Output:
    'R' if last painted stripe was a red row, 'B' if last was a blue column.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 8;
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::vector<std::string> v(N); // Store the 8x8 grid
    for (long p = 0; p < N; p++) {
      std::cin >> v[p]; // Read each row
    }
    char ans('.'); // Initialize answer to '.' (unfound)
    
    // Check if any row is all 'R' (red stripe painted last)
    for (long row = 0; ans == '.' && row < N; row++) {
      bool test(true);
      for (long col = 0; test && col < N; col++) {
        if (v[row][col] != 'R') { // If any cell in this row is not 'R'
          test = false;           // This is not a full red row
        }
      }
      if (test) {
        ans = 'R'; // Found a full red row -> red was last painted
      }
    }

    // Check if any column is all 'B' (blue stripe painted last)
    for (long col = 0; ans == '.' && col < N; col++) {
      bool test(true);
      for (long row = 0; test && row < N; row++) {
        if (v[row][col] != 'B') { // If any cell in this column is not 'B'
          test = false;           // This is not a full blue column
        }
      }
      if (test) {
        ans = 'B'; // Found a full blue column -> blue was last painted
      }
    }
    
    std::cout << ans << std::endl; // Output result for current test case
  }
}


// https://github.com/VaHiX/codeForces/