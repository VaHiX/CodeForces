// Problem: CF 2069 B - Set of Strangers
// https://codeforces.com/contest/2069/problem/B

/*
B. Set of Strangers
Algorithm: 
  - For each color in the grid, determine if it has adjacent cells (sharing a side) or not.
  - Color that has no adjacent cells is considered isolated.
  - Color that has adjacent cells is considered adjacent.
  - Each isolated color contributes 1 step to final result.
  - Each adjacent color contributes 2 steps to final result.
  - If there are any adjacent colors, subtract 2 from final result; otherwise, subtract 1.

Time Complexity: O(n * m), where n and m are dimensions of the grid. Each cell is visited once.
Space Complexity: O(k), where k is the number of distinct colors in the grid. 

*/

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] nm = Console.ReadLine().Split();
      int n = int.Parse(nm[0]);
      int m = int.Parse(nm[1]);
      int[,] grid = new int[n, m];
      for (int i = 0; i < n; i++) {
        string[] row = Console.ReadLine().Split();
        for (int j = 0; j < m; j++) {
          grid[i, j] = int.Parse(row[j]);
        }
      }
      Dictionary<int, int> colorMap = new Dictionary<int, int>();
      // Iterate over all cells to determine if a color is isolated or adjacent
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          int color = grid[i, j];
          if (!colorMap.ContainsKey(color))
            colorMap[color] = 0;
          // Check if current cell has adjacent cell with the same color horizontally or vertically
          if (j + 1 < m && grid[i, j + 1] == color)
            colorMap[color] = 1;
          if (i + 1 < n && grid[i + 1, j] == color)
            colorMap[color] = 1;
        }
      }
      int isolated = 0, adjacent = 0;
      // Count how many colors are isolated vs adjacent
      foreach (var value in colorMap.Values) {
        if (value == 0)
          isolated++;
        else
          adjacent++;
      }
      int result = isolated + 2 * adjacent;
      // Adjust result based on presence of adjacent cells
      Console.WriteLine(adjacent > 0 ? result - 2 : result - 1);
    }
  }
}


// https://github.com/VaHiX/codeForces/