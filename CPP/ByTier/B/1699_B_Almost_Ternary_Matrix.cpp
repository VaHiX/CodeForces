// Problem: CF 1699 B - Almost Ternary Matrix
// https://codeforces.com/contest/1699/problem/B

/*
 * Purpose: Generate a binary matrix of size n x m such that each cell has exactly
 *          two neighbors with a different value. The algorithm uses a cyclic pattern
 *          based on modulo 4 on row and column indices to ensure the constraint.
 *
 * Algorithm/Techniques: 
 *   - Use a pattern based on (row % 4) and (col % 4) to alternate values in a way 
 *     that ensures every cell has exactly two neighbors with different values.
 *   - The pattern is designed to create a structured checkerboard-like layout with 
 *     periodicity 4 in both directions.
 *
 * Time Complexity: O(n * m) per test case, as we iterate through all cells once.
 * Space Complexity: O(1) extra space, not counting the output matrix.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    for (long row = 1; row <= n; row++) {
      for (long col = 1; col <= m; col++) {
        // The formula ((row % 4 <= 1) != (col % 4 <= 1)) determines the value of the cell
        // based on the modulo 4 of row and column indices to ensure the constraint.
        printf("%d ", ((row % 4 <= 1) != (col % 4 <= 1)));
      }
      puts(""); // Print a newline after each row
    }
  }
}


// https://github.com/VaHiX/CodeForces/