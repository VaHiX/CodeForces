// Problem: CF 1739 A - Immobile Knight
// https://codeforces.com/contest/1739/problem/A

/*
 * Problem: Immobile Knight
 * Algorithm: Direct Computation
 * 
 * Purpose: For each test case, given n and m (dimensions of chessboard),
 * determine a cell (row, col) such that a knight placed there cannot move
 * to any other cell (i.e., the cell is isolated). If no such cell exists,
 * return any cell.
 * 
 * Key insight:
 * - On a 1xN or Nx1 board, all cells are isolated because a knight cannot move.
 * - On larger boards, it's generally possible for knights to move.
 * - The only isolated cell on a 3x3 board is the center (2,2).
 * - Thus, for small boards, we can hardcode the results based on these observations.
 * 
 * Time Complexity: O(1) - Constant time per test case.
 * Space Complexity: O(1) - No extra space used.
 */

#include <iostream>
int main() {
  int t, a;
  std::cin >> t;
  for (t *= 2; t--;) {  // Loop through twice the number of test cases to read two integers per case
    std::cin >> a;
    std::cout << (a + 1) / 2 << '\n';  // Compute and output result
  }
}


// https://github.com/VaHiX/CodeForces/