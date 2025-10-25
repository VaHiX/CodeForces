// Problem: CF 1598 A - Computer Game
// https://codeforces.com/contest/1598/problem/A

/*
 * Problem: A. Computer Game
 * Purpose: Determine if a character can traverse from top-left (1,1) to bottom-right (2,n)
 *          in a 2xN grid, avoiding traps ('1') and moving according to 8-directional adjacency.
 * 
 * Algorithm: 
 *   - For each test case, check if there exists a path from (1,1) to (2,n).
 *   - Key insight: If both rows have '1' at the same column index, it's impossible to pass through that column,
 *     because movement in the grid is restricted and we can't jump over traps.
 *   - We simple scan each column for conflicts where both rows have '1'.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) (ignoring input storage)
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;
    bool possible(true);
    for (long p = 0; p < a.size(); p++) {
      // If both cells in the same column are traps, path is blocked
      if (a[p] == '1' && b[p] == '1') {
        possible = false;
        break;
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/