// Problem: CF 754 B - Ilya and tic-tac-toe game
// https://codeforces.com/contest/754/problem/B

/*
 * Problem: Ilya and tic-tac-toe game
 * Algorithm: Check if Ilya (playing as X) can win in one move on a 4x4 board.
 * Approach: 
 *   1. Scan all possible 3-in-a-row combinations (horizontal, vertical, diagonal).
 *   2. For each such combination, check if placing an 'x' in an empty cell would complete it.
 *   3. If any such winning move exists, output "YES"; otherwise "NO".
 *
 * Time Complexity: O(1) - The board size is fixed at 4x4, so all loops have constant iterations.
 * Space Complexity: O(1) - A fixed-size vector and variables are used.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 4;
  std::vector<std::string> b(N);
  for (int p = 0; p < N; p++) {
    std::cin >> b[p];
  }
  bool res(false);
  // Check horizontal lines
  for (int row = 0; row < N; row++) {
    if (res) {
      break;
    }
    for (int col = 0; col < N - 2; col++) {
      if (res) {
        break;
      }
      // Check if three Xs or two Xs with one empty cell exist in a row
      res = (b[row][col] == 'x' && b[row][col + 1] == 'x' &&
             b[row][col + 2] == 'x') ||
            (b[row][col] == 'x' && b[row][col + 1] == 'x' &&
             b[row][col + 2] == '.') ||
            (b[row][col] == 'x' && b[row][col + 1] == '.' &&
             b[row][col + 2] == 'x') ||
            (b[row][col] == '.' && b[row][col + 1] == 'x' &&
             b[row][col + 2] == 'x');
    }
  }
  // Check vertical lines
  for (int col = 0; col < N; col++) {
    if (res) {
      break;
    }
    for (int row = 0; row < N - 2; row++) {
      if (res) {
        break;
      }
      // Check if three Xs or two Xs with one empty cell exist in a column
      res = (b[row][col] == 'x' && b[row + 1][col] == 'x' &&
             b[row + 2][col] == 'x') ||
            (b[row][col] == 'x' && b[row + 1][col] == 'x' &&
             b[row + 2][col] == '.') ||
            (b[row][col] == 'x' && b[row + 1][col] == '.' &&
             b[row + 2][col] == 'x') ||
            (b[row][col] == '.' && b[row + 1][col] == 'x' &&
             b[row + 2][col] == 'x');
    }
  }
  // Check main diagonal (top-left to bottom-right)
  for (int p = 0; p < N - 2; p++) {
    if (res) {
      break;
    }
    res = (b[p][p] == 'x' && b[p + 1][p + 1] == 'x' && b[p + 2][p + 2] == 'x') ||
          (b[p][p] == 'x' && b[p + 1][p + 1] == 'x' && b[p + 2][p + 2] == '.') ||
          (b[p][p] == 'x' && b[p + 1][p + 1] == '.' && b[p + 2][p + 2] == 'x') ||
          (b[p][p] == '.' && b[p + 1][p + 1] == 'x' && b[p + 2][p + 2] == 'x');
  }
  // Check anti-diagonal (top-right to bottom-left)
  for (int p = 0; p < N - 2; p++) {
    if (res) {
      break;
    }
    res = (b[p][N - p - 1] == 'x' && b[p + 1][N - p - 2] == 'x' &&
           b[p + 2][N - p - 3] == 'x') ||
          (b[p][N - p - 1] == 'x' && b[p + 1][N - p - 2] == 'x' &&
           b[p + 2][N - p - 3] == '.') ||
          (b[p][N - p - 1] == 'x' && b[p + 1][N - p - 2] == '.' &&
           b[p + 2][N - p - 3] == 'x') ||
          (b[p][N - p - 1] == '.' && b[p + 1][N - p - 2] == 'x' &&
           b[p + 2][N - p - 3] == 'x');
  }
  // Check additional diagonals that are not fully covered by loops above
  res = res || (b[0][1] == 'x' && b[1][2] == 'x' && b[2][3] == 'x') ||
        (b[0][1] == '.' && b[1][2] == 'x' && b[2][3] == 'x') ||
        (b[0][1] == 'x' && b[1][2] == '.' && b[2][3] == 'x') ||
        (b[0][1] == 'x' && b[1][2] == 'x' && b[2][3] == '.') ||
        (b[1][0] == 'x' && b[2][1] == 'x' && b[3][2] == 'x') ||
        (b[1][0] == '.' && b[2][1] == 'x' && b[3][2] == 'x') ||
        (b[1][0] == 'x' && b[2][1] == '.' && b[3][2] == 'x') ||
        (b[1][0] == 'x' && b[2][1] == 'x' && b[3][2] == '.') ||
        (b[0][2] == 'x' && b[1][1] == 'x' && b[2][0] == 'x') ||
        (b[0][2] == '.' && b[1][1] == 'x' && b[2][0] == 'x') ||
        (b[0][2] == 'x' && b[1][1] == '.' && b[2][0] == 'x') ||
        (b[0][2] == 'x' && b[1][1] == 'x' && b[2][0] == '.') ||
        (b[1][3] == 'x' && b[2][2] == 'x' && b[3][1] == 'x') ||
        (b[1][3] == '.' && b[2][2] == 'x' && b[3][1] == 'x') ||
        (b[1][3] == 'x' && b[2][2] == '.' && b[3][1] == 'x') ||
        (b[1][3] == 'x' && b[2][2] == 'x' && b[3][1] == '.');
  std::cout << (res ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/