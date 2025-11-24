// Problem: CF 493 D - Vasya and Chess
// https://codeforces.com/contest/493/problem/D

/*
 * Problem: Vasya and Chess
 * 
 * Algorithm/Approach:
 * This problem is a classic game theory problem involving optimal play on a chessboard.
 * The key insight is to analyze the symmetry and movement patterns of the queens:
 * 
 * 1. The white queen starts at (1, 1), and the black queen at (1, n).
 * 2. Both queens can move along rows, columns, and diagonals.
 * 3. The game ends when a player cannot capture any piece (i.e., no valid moves).
 * 4. The first player to have no valid move loses, unless their queen was captured.
 * 
 * By analyzing the structure:
 * - If n is odd, the center column (when n is odd) has no green pawns for the queens to avoid
 *   and the symmetry allows the black queen to win.
 * - If n is even, there is at least one symmetric position to block the opponent and force a win.
 * 
 * Time Complexity: O(1) - Only a single condition check.
 * Space Complexity: O(1) - No extra space used beyond input/output variables.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  if (n % 2) {  // If n is odd
    puts("black");  // Black wins
  } else {  // If n is even
    puts("white\n1 2");  // White wins, and the first move is to (1, 2)
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/