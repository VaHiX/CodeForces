// Problem: CF 745 B - Hongcow Solves A Puzzle
// https://codeforces.com/contest/745/problem/B

/*
 * Problem: Hongcow Solves A Puzzle
 * 
 * Task: Determine if two identical puzzle pieces can form a rectangle when placed side by side
 *       without rotation, flipping, or overlapping.
 * 
 * Approach:
 * - Identify the top and bottom boundaries of the non-empty rows in the puzzle piece.
 * - Check if all rows between these boundaries are identical.
 * - If they are, then placing two copies side by side will form a rectangle.
 * 
 * Time Complexity: O(n * m) where n is number of rows and m is number of columns.
 * Space Complexity: O(n * m) for storing the input grid.
 * 
 * Algorithms/Techniques: 
 * - Scan input to find top and bottom boundaries of the puzzle piece.
 * - Compare rows between boundaries to verify uniformity.
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::string empty(m, '.');
  std::vector<std::string> a(n);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];
  }
  long top(-1), bottom(n);
  for (long p = 0; p < n; p++) {
    if (a[p] == empty) {
      top = p;
    } else {
      break;
    }
  };
  ++top;
  for (long p = n - 1; p >= 0; p--) {
    if (a[p] == empty) {
      bottom = p;
    } else {
      break;
    }
  }
  long rectangle(true);
  for (long p = top; p < bottom; p++) {
    if (a[p] != a[top]) {
      rectangle = false;
      break;
    }
  }
  puts(rectangle ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/