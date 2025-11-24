// Problem: CF 1179 B - Tolik and His Uncle
// https://codeforces.com/contest/1179/problem/B

/*
 * Code Purpose: This program solves the problem of traversing an n x m grid 
 *               such that each cell is visited exactly once, and no vector 
 *               (dx, dy) between consecutive cells is repeated.
 *               The solution uses a clever traversal pattern that alternates 
 *               direction to cover all cells efficiently.
 *
 * Algorithms/Techniques: 
 *   - Simulated traversal using arithmetic progression and alternating 
 *     direction to cover grid.
 *   - Uses a single loop with a complex loop condition to determine
 *     the order of visit.
 *
 * Time Complexity: O(n * m) - We visit each cell once.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  // Loop to generate the order of visiting cells
  // col: cumulative column index, row: remaining rows to process, d: direction multiplier
  for (long col = 0, row = n * m - 1, d = 1; row >= 0;
       col += d * row, row--, d *= -1) {
    // Print the row and column coordinates of the current cell
    // col / m + 1: calculates the row number (1-indexed)
    // col % m + 1: calculates the column number (1-indexed)
    printf("%ld %ld\n", col / m + 1, col % m + 1);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/