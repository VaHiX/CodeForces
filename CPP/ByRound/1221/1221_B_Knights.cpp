// Problem: CF 1221 B - Knights
// https://codeforces.com/contest/1221/problem/B

/*
 * Problem: Knights
 * Purpose: To place white and black knights on an n x n chessboard such that 
 *          the number of duels (pairs of knights of different colors attacking each other) is maximized.
 * 
 * Algorithm/Technique:
 * - The key insight is to color the board in a checkerboard pattern.
 * - By placing knights in a checkerboard pattern, we maximize the number of adjacent cells
 *   (in terms of knight moves) that are of different colors.
 * - This is because a knight attacks cells that are two steps in one direction and one step in another,
 *   so by alternating colors in a checkerboard, we ensure that knights of different colors are placed
 *   in positions where they can attack each other.
 * 
 * Time Complexity: O(n^2)
 * - We iterate through all n x n cells once to print the board layout.
 * 
 * Space Complexity: O(1)
 * - We only use a constant amount of extra space to store the loop variables and board output.
 */

#include <cstdio>

int main() {
  long n;
  scanf("%ld", &n);
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < n; col++) {
      // Determine color based on sum of row and column indices
      // If (row + col) is odd, place 'W' (white), otherwise 'B' (black)
      putchar((row + col) % 2 ? 'W' : 'B');
    }
    puts(""); // Move to next line after printing each row
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/