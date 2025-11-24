// Problem: CF 1929 B - Sasha and the Drawing
// https://codeforces.com/contest/1929/problem/B

/*
 * Problem: Sasha and the Drawing
 * Purpose: Determine the minimum number of cells to color in an n×n grid such that at least k diagonals have at least one colored cell.
 * 
 * Algorithm:
 * - The grid has 4n - 2 diagonals in total.
 * - Each cell can cover at most 2 diagonals (one main diagonal and one anti-diagonal).
 * - To minimize the number of cells, we try to cover as many unique diagonals as possible per cell.
 * - If k <= (4n - 4), we can cover k diagonals with (k + 1) / 2 cells (since each cell covers at most 2 diagonals).
 * - If k > (4n - 4), we use a greedy approach: after placing cells to cover (4n - 4) diagonals optimally (with (4n - 4)/2 cells),
 *   we need to cover the remaining (k - (4n - 4)) diagonals, which requires exactly (k - (4n - 4)) additional cells.
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using fixed amount of memory for variables
 */

using System;
public class SashaAndTheDrawing {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split(); // Read n and k from input
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      int d = 4 * n - 2; // Total number of diagonals in the grid
      // Compute the minimal number of cells needed based on the value of k
      int ans = (k <= d - 2 ? (k + 1) / 2 : (d - 2) / 2 + k - (d - 2));
      Console.WriteLine(ans); // Output result for current test case
    }
  }
}


// https://github.com/VaHiX/CodeForces/