// Problem: CF 1365 A - Matrix Game
// https://codeforces.com/contest/1365/problem/A

/*
 * Problem: Matrix Game
 * Algorithms/Techniques: Greedy, Game Theory
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n + m) per test case
 *
 * Description:
 * Two players (Ashish and Vivek) play a game on an n x m matrix.
 * Cells are either 0 (unclaimed) or 1 (claimed).
 * On each turn, a player must claim a cell that is unclaimed and does not share
 * a row or column with any already claimed cells.
 * The player who cannot make a move loses.
 * Determine the winner assuming optimal play.
 *
 * Approach:
 * - For each row and column, we mark whether it's "available" (no cells in it are claimed).
 * - Initially all rows and cols are available.
 * - When we encounter a 1 in the matrix, we mark that row and column as unavailable.
 * - After processing, count how many rows and columns are still available.
 * - The number of moves possible is min(available_rows, available_cols).
 * - If this number is odd, Ashish (who starts first) wins; otherwise Vivek wins.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<bool> rows(n, 1);   // Tracks available rows
    std::vector<bool> cols(m, 1);   // Tracks available columns
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        long x;
        scanf("%ld", &x);
        if (!x) {
          continue;   // Skip unclaimed cells
        }
        rows[row] = 0;  // Mark row as unavailable
        cols[col] = 0;  // Mark column as unavailable
      }
    }
    long u(0);   // Count of available rows
    for (long p = 0; p < n; p++) {
      u += rows[p];
    }
    long v(0);   // Count of available columns
    for (long p = 0; p < m; p++) {
      v += cols[p];
    }
    long turns = (u < v) ? u : v;   // Maximum possible moves
    puts((turns % 2) ? "Ashish" : "Vivek");   // Ashish wins if odd number of moves
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/