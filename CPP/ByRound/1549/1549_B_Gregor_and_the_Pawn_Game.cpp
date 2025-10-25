// Problem: CF 1549 B - Gregor and the Pawn Game
// https://codeforces.com/contest/1549/problem/B

/*
Purpose: Solve the problem of determining the maximum number of Gregor's pawns that can reach the first row of a chessboard.
         Each pawn can move up or diagonally up if there's an enemy pawn in the destination, and all moves are simulated greedily.

Algorithm:
- Greedily process each pawn from left to right.
- For each pawn that can advance (i.e., its target cell is '0'):
  - Try to move it directly upward if possible.
  - Otherwise, try to move it diagonally up if there's an enemy pawn in the diagonal cell.
  - If a move is made, mark that position as occupied ('x').

Time Complexity: O(n) per test case, where n is the size of the board. Each cell is processed at most once.
Space Complexity: O(n) for storing the strings and auxiliary variables.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string b, w;
    std::cin >> b >> w;
    long cnt(0);
    for (long p = 0; p < n; p++) {
      // If there's no pawn at this position, skip
      if (w[p] == '0') {
        continue;
      }
      // Try to move the pawn directly up if possible
      if (p > 0 && b[p - 1] == '1') {
        b[p - 1] = 'x'; // Mark cell as occupied after move
        ++cnt;
      } else if (b[p] == '0') { // If current position is empty, move pawn up
        b[p] = 'x';
        ++cnt;
      } else if (p + 1 < n && b[p + 1] == '1') { // Try diagonal move to right
        b[p + 1] = 'x';
        ++cnt;
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/