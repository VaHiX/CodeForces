// Problem: CF 924 A - Mystical Mosaic
// https://codeforces.com/contest/924/problem/A

/*
 * Problem: Mystical Mosaic
 * 
 * Algorithm/Technique:
 * - This solution uses a greedy approach to validate if a given grid can be
 *   generated using the described operations.
 * - For each column, it tracks the first row that has a black cell in that column.
 * - When a black cell is encountered in a column, we check if it's consistent
 *   with previous rows in that column.
 * - Additionally, we check that no row can have a black cell that belongs to
 *   a column that already has a black cell from a different operation.
 * 
 * Time Complexity: O(n * m)
 * Space Complexity: O(m)
 */
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  bool possible(true);
  std::vector<long> color(m, 0); // Tracks the first row where a column turned black
  for (long row = 1; row <= n; row++) {
    std::string s;
    std::cin >> s;
    long cur(-1); // Tracks the current operation's row identifier
    for (int col = 0; col < m; col++) {
      if (s[col] == '#') {
        // If this column was not previously marked by any operation
        if (!color[col]) {
          color[col] = row; // Mark it as belonging to current row
        }
        if (cur == -1) {
          cur = color[col]; // Initialize operation identifier
        }
        // If this column's operation id doesn't match current operation id
        if (cur != color[col]) {
          possible = false;
        }
      } else if (color[col] == cur) {
        // If this position is white but the column still belongs to current operation
        possible = false;
      }
    }
  }
  puts(possible ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/