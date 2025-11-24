// Problem: CF 844 B - Rectangles
// https://codeforces.com/contest/844/problem/B

/*
 * Purpose: Count the number of valid sets of cells in an n×m grid such that:
 *          1. All cells in a set have the same color (0 or 1)
 *          2. Every two cells in a set share a row or column
 * 
 * Algorithm:
 * - For each row, calculate the number of black cells (r[p])
 * - For each column, calculate the number of black cells (c[p])
 * - A valid set is a subset of cells in a single row or column where all cells have the same color.
 * - For each row with `r[p]` black cells, we count all non-empty subsets of those cells.
 *   This equals (2^r[p] - 1) for black cells and (2^(m - r[p]) - 1) for white cells.
 * - Same logic applies to columns.
 * - Total count is computed using inclusion-exclusion principle.
 * 
 * Time Complexity: O(n * m) - processing each cell once to compute row/column sums
 * Space Complexity: O(n + m) - storing row and column sums
 */

#include <stdint.h>
#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  std::vector<int> r(n, 0);  // Count of black cells per row
  std::vector<int> c(m, 0);  // Count of black cells per column
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < m; col++) {
      int x;
      scanf("%d", &x);
      r[row] += x;   // Accumulate black cells in row
      c[col] += x;   // Accumulate black cells in column
    }
  }
  int64_t total(-n * m);  // Start with negative count of all cells (to avoid overcounting single cells)
  for (long p = 0; p < n; p++) {
    // For each row, add contributions from subsets of black and white cells
    total += ((1LL << r[p]) - 1) + ((1LL << (m - r[p])) - 1);
  }
  for (long p = 0; p < m; p++) {
    // For each column, add contributions from subsets of black and white cells
    total += ((1LL << c[p]) - 1) + ((1LL << (n - c[p])) - 1);
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/