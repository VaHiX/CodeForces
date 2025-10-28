// Problem: CF 1850 C - Word on the Paper
// https://codeforces.com/contest/1850/problem/C

/*
 * C. Word on the Paper
 *
 * Problem Description:
 * Given an 8x8 grid of characters where each character is either a dot '.' or a lowercase letter,
 * a word is written vertically in one column from top to bottom. The task is to find and output
 * that word.
 *
 * Algorithms/Techniques:
 * - Brute force scanning of the grid to find the first non-dot character
 * - Traverse downward from that position until a dot is encountered
 *
 * Time Complexity: O(t * B^2)
 *   - t: number of test cases
 *   - B: size of the grid (8 in this case)
 *   - For each test case, we scan up to B^2 cells to find the starting point,
 *     then traverse at most B more cells vertically.
 *
 * Space Complexity: O(B^2)
 *   - We store the 8x8 grid of strings for each test case.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int B = 8;
  long t;
  std::cin >> t;
  while (t--) {
    std::vector<std::string> m(B);         // Store the 8x8 grid
    for (long p = 0; p < B; p++) {        // Read each row of the grid
      std::cin >> m[p];
    }
    int sr(-1), sc(-1);                   // Start row and column for the word
    for (int row = 0; sr < 0 && row < B; row++) {  // Find first non-dot character
      for (int col = 0; sc < 0 && col < B; col++) {
        if (m[row][col] != '.') {
          sr = row;
          sc = col;
        }
      }
    }
    std::string res("");                  // Result string to build the word
    for (int row = sr; row < B && m[row][sc] != '.'; row++) {  // Traverse downward
      res += m[row][sc];                  // Append character to result
    }
    std::cout << res << std::endl;        // Output the constructed word
  }
}


// https://github.com/VaHiX/codeForces/