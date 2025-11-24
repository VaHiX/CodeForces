// Problem: CF 1333 A - Little Artem
// https://codeforces.com/contest/1333/problem/A

/*
Code Purpose:
This program solves the problem of finding a good coloring for an n x m grid such that 
the number of black cells with at least one white neighbor (B) equals the number of 
white cells with at least one black neighbor (W) plus 1. 

The approach uses a simple checkerboard-like pattern, with a special case for the 
top-left cell to ensure the difference B = W + 1 is satisfied.

Algorithms/Techniques:
- Checkerboard pattern generation with exception for top-left cell.
- Time and space complexity are determined by the grid size.

Time Complexity: O(n * m) where n is number of rows and m is number of columns.
Space Complexity: O(1) excluding the output storage.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long R, C;
    scanf("%ld %ld", &R, &C);
    for (long row = 0; row < R; row++) {
      for (long col = 0; col < C; col++) {
        // Special case for top-left cell: 'W' to adjust B and W balance
        // For all other cells, alternate between 'B' and 'W' based on (row + col)
        printf("%c", (row + col == 0) ? 'W' : 'B');
      }
      puts(""); // Newline after each row
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/