// Problem: CF 1438 C - Engineer Artem
// https://codeforces.com/contest/1438/problem/C

/*
 * Code purpose: 
 *   This program takes a matrix of integers and transforms it into a "good" matrix,
 *   where no two adjacent cells have the same value. It does so by incrementing
 *   some values by 1, ensuring that adjacent cells differ.
 *
 * Algorithm/Technique:
 *   - The solution uses a coloring scheme based on the parity of row and column indices.
 *   - For each cell (i, j), a value u is calculated as (i % 2) ^ (j % 2).
 *   - If the original value x has the same parity as u, we add 1 to x.
 *   - This ensures adjacent cells have different parities, which prevents same values.
 *
 * Time Complexity: O(n * m) where n is number of rows and m is number of columns.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long nrow, ncol;
    scanf("%ld %ld", &nrow, &ncol);
    for (long row = 0; row < nrow; row++) {
      for (long col = 0; col < ncol; col++) {
        // Calculate a parity-based color value for the cell (row, col)
        long u = ((row % 2) ^ (col % 2));
        long x;
        scanf("%ld", &x);
        // Increment x if x and u have the same parity
        x += ((x % 2) != (u % 2));
        printf("%ld ", x);
      }
      puts(""); // Print newline after each row
    }
  }
}


// https://github.com/VaHiX/CodeForces/