// Problem: CF 710 A - King Moves
// https://codeforces.com/contest/710/problem/A

/*
Purpose: Determine the number of valid moves a king can make from a given position on a chess board.
Algorithm: 
- Parse the input position to get column (letter) and row (digit)
- Check if the king is on the edge of the board (column a or h, or row 1 or 8)
- Based on edge conditions, determine the number of moves:
  - Corner position (both edge) = 3 moves
  - Edge position (one edge) = 5 moves  
  - Middle position (no edges) = 8 moves

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant space usage (string of fixed size)
*/

#include <cstdio>
#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  // Check if king is on left or right edge (column a or h)
  bool hor = (s[0] == 'a') || (s[0] == 'h');
  // Check if king is on top or bottom edge (row 1 or 8)
  bool ver = (s[1] == '1') || (s[1] == '8');
  // If king is on both edges (corner position), it has 3 possible moves
  if (hor && ver) {
    puts("3");
  } else if (hor || ver) {
    // If king is on only one edge, it has 5 possible moves
    puts("5");
  } else {
    // If king is not on any edge (middle position), it has 8 possible moves
    puts("8");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/