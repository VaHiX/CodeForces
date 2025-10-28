// Problem: CF 1926 B - Vlad and Shapes
// https://codeforces.com/contest/1926/problem/B

/*
 * Problem: B. Vlad and Shapes
 * Purpose: Determine whether a given binary grid represents a triangle or a square
 *          made up of '1's.
 *
 * Algorithm:
 *   - For each test case, read the grid row by row.
 *   - Count the number of '1's in each row.
 *   - Check for triangle properties:
 *     * The number of '1's should follow either an increasing or decreasing pattern
 *       (like a pyramid) with no two rows having the same count of '1's.
 *   - If the pattern matches a square (constant number of '1's per row), output "SQUARE".
 *   - If it does not match a square, it must be a triangle.
 *
 * Time Complexity: O(n^2) where n is the size of the grid.
 *                  Each cell is read once, and for each row we count '1's in O(n) time.
 * Space Complexity: O(1) - only using fixed extra variables; no additional data structures.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    bool triangle(true);  // Assume it's a triangle initially
    long prev(0);         // Previous row's count of '1's
    for (long row = 0; row < n; row++) {
      std::string s;
      std::cin >> s;
      long ones(0);
      for (long col = 0; col < s.size(); col++) {
        ones += (s[col] == '1');  // Count number of '1's in current row
      }
      if (ones > 0 && prev > 0 && ones == prev) {
        triangle = false;  // If two rows have same number of '1's, not a triangle -> must be square
      }
      prev = ones;  // Store the count for next iteration
    }
    std::cout << (triangle ? "TRIANGLE" : "SQUARE") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/