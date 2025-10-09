// Problem: CF 1997 B - Make Three Regions
// https://codeforces.com/contest/1997/problem/B

/*
B. Make Three Regions
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm:
The problem asks to count the number of free cells such that blocking them creates exactly 3 connected regions in a 2-row, n-column grid.

Approach:
- For each valid column index (from 1 to n-2), check if the cell at (0, col) and (1, col) can form a pattern where blocking this cell splits the grid into exactly 3 regions.
- The key insight is that we want to look for 'U' shapes formed by free cells in adjacent columns that, when one central cell is blocked, would fragment the region into three parts.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm processes each column once, making a constant number of checks per column.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::string> v(2);
    std::cin >> v[0] >> v[1];
    long cnt(0);
    for (long col = 1; col + 1 < v[0].size(); col++) { // Iterate through valid columns to check patterns
      for (long row = 0; row < 2; row++) {
        // Skip if any of the three horizontal adjacent cells contain 'x'
        if (v[row][col - 1] == 'x' || v[row][col] == 'x' ||
            v[row][col + 1] == 'x') {
          continue;
        }
        // Skip if the vertically opposite cell contains 'x'
        if (v[1 - row][col] == 'x') {
          continue;
        }
        // Check if vertical neighbors of current cell are free ('.')
        if (v[1 - row][col - 1] == '.' || v[1 - row][col + 1] == '.') {
          continue;
        }
        ++cnt; // Found a valid pattern
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/