// Problem: CF 2101 A - Mex in the Grid
// https://codeforces.com/contest/2101/problem/A

/*
 * Problem: A. Mex in the Grid
 * Algorithm: Spiral filling approach to maximize MEX sum over all subgrids
 * Time Complexity: O(n^2) per test case
 * Space Complexity: O(n^2) for the grid storage
 *
 * This solution fills the grid in a spiral pattern starting from the top-left corner,
 * moving right, then down, then left, then up, repeating until all cells are filled.
 * The spiral ensures a natural distribution of values that helps maximize the MEX sum.
 */

using System;
public class Solution {
  static bool inside(int x, int n) { return x >= 0 && x < n; }
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()); // Read grid size
      int[,] grid = new int[n, n]; // Initialize grid with -1
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          grid[i, j] = -1;
      int x = 0, y = 0, z = 1, val = n * n - 1; // Start position and direction
      int[] dx = { -1, 0, 1, 0 }; // Direction deltas for up, right, down, left
      int[] dy = { 0, 1, 0, -1 };
      while (val >= 0) {
        grid[x, y] = val--; // Fill current cell with value
        // Check if we need to turn (hit boundary or already filled cell)
        if (!inside(x + dx[z], n) || !inside(y + dy[z], n) ||
            grid[x + dx[z], y + dy[z]] > -1)
          z = (z + 1) % 4; // Turn clockwise
        x += dx[z]; // Move in current direction
        y += dy[z];
      }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
          Console.Write(grid[i, j] + " ");
        Console.WriteLine();
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/