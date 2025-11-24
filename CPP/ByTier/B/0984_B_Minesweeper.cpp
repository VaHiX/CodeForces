// Problem: CF 984 B - Minesweeper
// https://codeforces.com/contest/984/problem/B

/*
Code purpose: This program checks if a given Minesweeper field is valid according to the rules of the game.
              For each cell:
              - If it's a digit k, exactly k neighboring cells must contain bombs.
              - If it's empty (.), all neighboring cells must be empty.
              - If it's a bomb (*), it is always valid.

Algorithms/Techniques: 
- Iterative validation of each cell in the grid.
- For each cell, we check its 8 neighbors to count bombs.
- Handle edge cases for grid boundaries.

Time Complexity: O(n * m * 8) = O(n * m), where n and m are the dimensions of the grid. 
Space Complexity: O(n * m), to store the grid of characters.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::vector<std::string> b(n);
  for (long p = 0; p < n; p++) {
    std::cin >> b[p];
  }
  bool valid(true);
  for (long row = 0; row < n; row++) {
    if (!valid) {
      break;
    }
    for (long col = 0; col < b[row].size(); col++) {
      if (!valid) {
        break;
      }
      // Skip bombs since they don't need validation
      if (b[row][col] == '*') {
        continue;
      }
      long cnt;
      // Determine the expected number of bombs (from digit) or 0 (from empty cell)
      if (b[row][col] == '.') {
        cnt = 0;
      } else {
        cnt = b[row][col] - '0';
      }
      long bombs(0);
      // Check all 8 neighboring cells
      for (long dr = -1; dr <= 1; dr++) {
        for (long dc = -1; dc <= 1; dc++) {
          if (dr == 0 && dc == 0) {
            continue; // Skip the cell itself
          }
          // Ensure neighbor is within bounds
          if (row + dr < 0 || row + dr >= n) {
            continue;
          }
          if (col + dc < 0 || col + dc >= m) {
            continue;
          }
          // Count bombs
          if (b[row + dr][col + dc] == '*') {
            ++bombs;
          }
        }
      }
      // Compare the expected number of bombs with actual
      if (cnt != bombs) {
        valid = false;
        break;
      }
    }
  }
  std::cout << (valid ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/