// Problem: CF 1621 A - Stable Arrangement of Rooks
// https://codeforces.com/contest/1621/problem/A

/*
 * Code Purpose:
 * This program finds a stable arrangement of k rooks on an n x n chessboard.
 * A stable arrangement means:
 * 1. No two rooks attack each other (good arrangement).
 * 2. No single rook can be moved to an adjacent cell without making the arrangement
 *    no longer good (i.e., no rook can be safely moved).
 *
 * Algorithm:
 * - For small k (k <= (n + 1)/2), place rooks on alternating rows to ensure no two
 *   rooks are adjacent or on the same row/column.
 * - If k > (n + 1) / 2, then it's impossible to place k rooks without violating stability.
 *
 * Time Complexity: O(n^2) - We iterate through each row and fill each row with characters.
 * Space Complexity: O(n^2) - We construct and store the board representation in a string.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    if (2 * k > n + 1) {  // If k exceeds a threshold, it's impossible to have a stable arrangement
      std::cout << -1 << std::endl;
      continue;
    }
    long rem(k);  // Remaining rooks to place
    for (long p = 0; p < n; p++) {
      std::string s(n, '.');  // Initialize a row with all dots (empty cells)
      if (p % 2 == 0 && rem > 0) {  // Place rook on even rows, if we still have rooks to place
        s[p] = 'R';  // Place the rook at position p (column p) on this row
        --rem;  // Decrease the count of remaining rooks
      }
      std::cout << s << std::endl;  // Output the constructed row
    }
  }
}


// https://github.com/VaHiX/CodeForces/