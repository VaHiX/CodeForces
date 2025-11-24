// Problem: CF 1717 B - Madoka and Underground Competitions
// https://codeforces.com/contest/1717/problem/B

/*
B. Madoka and Underground Competitions

Purpose:
This program generates a good n×n grid (where n is multiple of k) containing only '.' and 'X',
such that:
- Every k×1 or 1×k subtable has at least one 'X'
- The number of 'X's is minimized
- Cell (r, c) must contain 'X'

Algorithm:
The solution uses a periodic pattern based on modular arithmetic.
For each cell (row, col), we determine whether to place 'X' or '.' using:
(row + col - r - c) % k == 0

This ensures that:
1. Every k consecutive cells in any row/column have at least one 'X'
2. The specified position (r,c) is always 'X'
3. Minimum number of 'X's are used

Time Complexity: O(n^2) - iterate through all n×n cells once
Space Complexity: O(1) - only storing input and temporary variables

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, r, c;
    scanf("%ld %ld %ld %ld", &n, &k, &r, &c);
    --r;   // Convert to 0-based indexing
    --c;   // Convert to 0-based indexing
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        // Determine if current cell should be 'X' or '.'
        // Using periodic pattern based on (row + col - r - c) modulo k
        putchar((row + col - r - c) % k ? '.' : 'X');
      }
      puts("");  // Newline after each row
    }
  }
}


// https://github.com/VaHiX/codeForces/