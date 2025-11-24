// Problem: CF 1907 A - Rook
// https://codeforces.com/contest/1907/problem/A

/*
Purpose: This program computes all possible moves for a rook on a chessboard given its current position.
         The rook can move vertically or horizontally any number of squares, but cannot move to its own position.
         For each test case, it outputs all such valid moves in the standard chess notation (e.g., "d5").

Algorithms/Techniques: 
    - Iteration over rows and columns to generate all valid moves
    - String manipulation to construct output in correct format

Time Complexity: O(1) per test case, since the board size is fixed at 8x8, and we iterate over a constant number of squares.
Space Complexity: O(1), as no extra space is used apart from input/output variables.

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Loop through all rows (1 to 8) and print moves in the same column but different rows
    for (char col = '1'; col <= '8'; col++) {
      if (col != s[1]) { // Skip the current row
        std::cout << s[0] << col << std::endl;
      }
    }
    // Loop through all columns (a to h) and print moves in the same row but different columns
    for (char row = 'a'; row <= 'h'; row++) {
      if (row != s[0]) { // Skip the current column
        std::cout << row << s[1] << std::endl;
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/