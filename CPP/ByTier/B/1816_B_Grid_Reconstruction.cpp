// Problem: CF 1816 B - Grid Reconstruction
// https://codeforces.com/contest/1816/problem/B

/*
 * Problem: Grid Reconstruction
 * 
 * Purpose: To place integers 1 to 2n on a 2×n grid such that the minimum cost
 *          over all paths from (1,1) to (2,n) is maximized.
 * 
 * Algorithm/Technique:
 * - Greedily construct the grid to balance path costs.
 * - Use alternating assignment of values to rows to optimize the minimum path cost.
 * 
 * Time Complexity: O(n) per test case, as we iterate through columns once.
 * Space Complexity: O(n) per test case, for storing the 2×n grid.
 * 
 * Strategy:
 * - Place 2*n - 1 at (1, 0) and 2*n at (2, n-1).
 * - For each subsequent column p:
 *   - If p is odd, assign (p + 1) to (1, p) and p to (2, p - 1)
 *   - If p is even, assign (n + p) to (1, p) and (n + p - 1) to (2, p - 1)
 * 
 * This ensures that path costs are balanced and the minimum cost is maximized.
 */

#include <cstdio>
#include <vector>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::vector<long>> v(2, std::vector<long>(n, 0));
    v[0][0] = 2 * n - 1;     // Place largest odd number at top-left
    v[1][n - 1] = 2 * n;     // Place largest number at bottom-right
    
    // Fill the rest of the grid in a specific pattern
    for (long p = 1; p < n; p++) {
      if (p % 2) {
        // For odd p: assign small odd numbers to top row, small even to bottom row
        v[0][p] = p + 1;     // Assign odd number to top row
        v[1][p - 1] = p;     // Assign even number to bottom row
      } else {
        // For even p: assign larger numbers to top row, smaller to bottom
        v[0][p] = n + p;     // Assign large number to top row
        v[1][p - 1] = n + p - 1; // Assign slightly smaller to bottom row
      }
    }
    
    // Output the constructed grid
    for (long row = 0; row < 2; row++) {
      for (long col = 0; col < n; col++) {
        printf("%ld ", v[row][col]);
      }
      puts(""); // Newline after each row
    }
  }
}


// https://github.com/VaHiX/CodeForces/