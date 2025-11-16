// Problem: CF 907 B - Tic-Tac-Toe
// https://codeforces.com/contest/907/problem/B

/*
 * Purpose: Solve a modified Tic-Tac-Toe game where moves are restricted based on the previous move.
 *          The game is played on a 9x9 grid divided into 3x3 subgrids (fields).
 *          The player must place their chip in the subgrid corresponding to the last move's position,
 *          unless that subgrid is full, in which case any empty cell is valid.
 *
 * Algorithms/Techniques:
 *   1. Parse input as a 9x9 grid (represented as 9 rows of 9 characters)
 *   2. Determine which subgrid (3x3) was last played in based on coordinates
 *   3. If the subgrid is not full, find all empty cells in that subgrid and mark them
 *   4. If the subgrid is full, find all empty cells in the entire grid and mark them
 *   5. Output the grid with '!' to indicate valid moves
 *
 * Time Complexity: O(1) - since the grid size is fixed (9x9)
 * Space Complexity: O(1) - since the grid size is fixed and no additional space is used
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 3;
  std::vector<std::string> v(N * N); // Store 9 rows of the 9x9 grid
  for (int row = 0; row < N * N; row++) {
    for (int col = 0; col < N; col++) {
      std::string x;
      std::cin >> x;
      v[row] += x;
    }
  }
  int lr, lc;
  std::cin >> lr >> lc;
  --lr; // Convert to 0-based indexing
  --lc;
  int wr(lr % N), wc(lc % N); // Determine which 3x3 subgrid (row, col)
  bool found(false);
  for (int rr = 0; rr < N; rr++) {
    for (int cc = 0; cc < N; cc++) {
      if (v[N * wr + rr][N * wc + cc] == '.') { // Check each position in the target subgrid
        v[N * wr + rr][N * wc + cc] = '!'; // Mark valid move
        found = true;
      }
    }
  }
  if (!found) { // If no empty spots in the designated subgrid
    for (int row = 0; row < v.size(); row++) {
      for (int p = 0; p < v[row].size(); p++) {
        if (v[row][p] == '.') {
          v[row][p] = '!'; // Mark all empty cells as valid moves
        }
      }
    }
  }
  for (int row = 0; row < v.size(); row++) {
    for (int p = 0; p < v[row].size(); p++) {
      std::cout << v[row][p];
      if (p % N == 2 && (p + 1 < v.size())) {
        std::cout << " "; // Add spacing between 3x3 subgrids
      }
    }
    std::cout << std::endl;
    if (row % 3 == 2) {
      std::cout << std::endl; // Add blank line after every 3 rows
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/