// Problem: CF 508 A - Pasha and Pixels
// https://codeforces.com/contest/508/problem/A

/*
 * Problem: Pasha and Pixels
 * Purpose: Determine the move number when a 2x2 square of black pixels is formed
 *          in a grid after sequential pixel coloring according to a plan.
 *
 * Algorithm/Techniques:
 *   - Simulation of grid coloring with tracking of 2x2 squares
 *   - For each move, check the four possible 2x2 squares that could include the newly painted pixel
 *   - Use a boolean grid to represent the field state
 *
 * Time Complexity: O(k * n * m) in worst case where k is the number of moves,
 *                  but effectively much lower due to early termination on finding a 2x2 square.
 * Space Complexity: O(n * m) for storing the grid state.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m, k;
  scanf("%ld %ld %ld\n", &n, &m, &k);
  std::vector<std::vector<bool>> field(n, std::vector<bool>(m, 0)); // Initialize grid with all white pixels
  long output(0); // Store the move number when 2x2 square is formed, 0 if not formed
  for (long p = 1; p <= k; p++) {
    long row, col;
    scanf("%ld %ld\n", &row, &col);
    --row;
    --col;
    field[row][col] = 1; // Color the pixel black
    
    // Check for 2x2 square formed with current pixel as top-left
    if (row > 0 && col > 0 && field[row - 1][col] && field[row][col - 1] &&
        field[row - 1][col - 1]) {
      output = p;
      break;
    }
    
    // Check for 2x2 square formed with current pixel as top-right
    if (row > 0 && col < m - 1 && field[row - 1][col] && field[row][col + 1] &&
        field[row - 1][col + 1]) {
      output = p;
      break;
    }
    
    // Check for 2x2 square formed with current pixel as bottom-left
    if (row < n - 1 && col > 0 && field[row + 1][col] && field[row][col - 1] &&
        field[row + 1][col - 1]) {
      output = p;
      break;
    }
    
    // Check for 2x2 square formed with current pixel as bottom-right
    if (row < n - 1 && col < m - 1 && field[row + 1][col] &&
        field[row][col + 1] && field[row + 1][col + 1]) {
      output = p;
      break;
    }
  }
  printf("%ld\n", output);
  return 0;
}


// https://github.com/VaHiX/CodeForces/