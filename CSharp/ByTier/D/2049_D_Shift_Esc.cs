// Problem: CF 2049 D - Shift + Esc
// https://codeforces.com/contest/2049/problem/D

/*
 * Problem: D. Shift + Esc
 * 
 * Algorithm: Dynamic Programming with Optimization
 * 
 * Time Complexity: O(n * m^2)
 * Space Complexity: O(m^2)
 * 
 * Approach:
 * - For each row, we precompute the minimum cost to reach each possible starting position
 *   after shifting that row left by s positions (0 to m-1).
 * - We use dynamic programming to compute the minimum cost from (1,1) to (n,m),
 *   considering that we can shift rows before moving.
 * - We optimize by keeping track of the minimum cost for each column across all shift values.
 * - For each row, we compute the minimum cost for reaching each column with a specific shift,
 *   using previously computed values.
 * 
 * Key Concepts:
 * - The cost function k*x + y, where x is number of shifts and y is sum of visited cells.
 * - For each row, we can shift it left by any number of positions (0 to m-1).
 * - For each position in a row and each shift value, we calculate a cost to reach this cell.
 * - We use dynamic programming to find optimal path from start to end.
 */

using System;
using System.Linq;
class Program {
  const long INF = (long)1e18;
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var inputs = Console.ReadLine().Split().Select(long.Parse).ToArray();
      int n = (int)inputs[0];
      int m = (int)inputs[1];
      long k = inputs[2];
      long[,] grid = new long[n, m];
      for (int i = 0; i < n; i++) {
        var row = Console.ReadLine().Split().Select(long.Parse).ToArray();
        for (int j = 0; j < m; j++) {
          grid[i, j] = row[j];
        }
      }
      // dpPrev[j, s] = minimum cost to reach column j in current row, with shift s
      long[,] dpPrev = new long[m, m];
      long[,] dpCurrent = new long[m, m];
      // Initialize dpPrev with infinity
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
          dpPrev[i, j] = INF;
        }
      }
      // Initialize first row with shifting operations
      for (int s = 0; s < m; s++) {
        dpPrev[0, s] = k * s + grid[0, (0 + s) % m]; // First cell of row 0 with shift s
      }
      // Process first row
      for (int j = 1; j < m; j++) {
        for (int s = 0; s < m; s++) {
          // Cost to reach (0,j) with shift s is cost from previous cell plus current cell value
          if (dpPrev[j - 1, s] + grid[0, (j + s) % m] < dpPrev[j, s]) {
            dpPrev[j, s] = dpPrev[j - 1, s] + grid[0, (j + s) % m];
          }
        }
      }
      // Process remaining rows
      for (int i = 1; i < n; i++) {
        // Reset dpCurrent for each new row
        for (int j = 0; j < m; j++) {
          for (int s = 0; s < m; s++) {
            dpCurrent[j, s] = INF;
          }
        }
        // Compute minimum cost for each column in previous row
        long[] minPrev = new long[m];
        for (int j = 0; j < m; j++) {
          minPrev[j] = INF;
          for (int sPrev = 0; sPrev < m; sPrev++) {
            if (dpPrev[j, sPrev] < minPrev[j]) {
              minPrev[j] = dpPrev[j, sPrev];
            }
          }
        }
        // Compute dpCurrent values for new row
        for (int s = 0; s < m; s++) {
          for (int j = 0; j < m; j++) {
            long cellVal = grid[i, (j + s) % m]; // Value of cell (i, j) with shift s
            if (j == 0) {
              // First column of row: no left movement, only from above
              long cost = minPrev[j] + k * s + cellVal;
              if (cost < dpCurrent[j, s]) {
                dpCurrent[j, s] = cost;
              }
            } else {
              // Regular columns: choose minimum path from above or left
              long costFromAbove = minPrev[j] + k * s + cellVal;
              long costFromLeft = dpCurrent[j - 1, s] + cellVal;
              dpCurrent[j, s] = Math.Min(dpCurrent[j, s],
                                         Math.Min(costFromAbove, costFromLeft));
            }
          }
        }
        // Transfer dpCurrent to dpPrev for next iteration
        Array.Copy(dpCurrent, dpPrev, dpCurrent.Length);
      }
      // Find minimum cost to reach the last column of the final row
      long answer = INF;
      for (int s = 0; s < m; s++) {
        answer = Math.Min(answer, dpPrev[m - 1, s]);
      }
      Console.WriteLine(answer);
    }
  }
}


// https://github.com/VaHiX/CodeForces/