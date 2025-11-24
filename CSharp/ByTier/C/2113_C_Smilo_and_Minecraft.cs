// Problem: CF 2113 C - Smilo and Minecraft
// https://codeforces.com/contest/2113/problem/C

/*
C. Smilo and Minecraft
Algorithms/Techniques: 2D Prefix Sum, Brute Force with Optimization
Time Complexity: O(n * m * k) per test case
Space Complexity: O(n * m)

The problem involves a grid where Smilo can place dynamite in empty cells ('.') to explode
and destroy a square area of size (2k+1) centered at that cell. Gold ('g') inside the square
that is not on the boundary disappears, but gold on the boundary is collected.

Approach:
1. Use 2D prefix sum array to quickly compute the total gold in any rectangular region.
2. For each empty cell ('.'), simulate placing dynamite and calculate how much gold would be lost.
3. The key insight: to maximize gain, minimize the gold lost by choosing an optimal explosion center.
4. Since the explosion area can extend beyond grid boundaries, boundary checks are needed.

*/

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      string[] input = Console.ReadLine().Split();
      int rows = int.Parse(input[0]);
      int cols = int.Parse(input[1]);
      int radius = int.Parse(input[2]); // k from problem description
      string[] grid = new string[rows];
      for (int i = 0; i < rows; i++) {
        grid[i] = Console.ReadLine();
      }
      int[,] prefixSum = new int[rows + 1, cols + 1]; // 1-indexed prefix sum
      int totalGold = 0;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          int isGold = grid[i][j] == 'g' ? 1 : 0;
          totalGold += isGold;
          // Build prefix sum: prefixSum[i+1, j+1] = sum of all cells in rectangle from (0,0) to (i,j)
          prefixSum[i + 1, j + 1] = prefixSum[i + 1, j] + prefixSum[i, j + 1] -
                                    prefixSum[i, j] + isGold;
        }
      }

      // Helper function to get gold count in region [x1,y1) to (x2,y2)
      int GetGoldInRegion(int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2)
          return 0;
        // Using 1-based indexing for prefix sum
        return prefixSum[x2 + 1, y2 + 1] - prefixSum[x1, y2 + 1] -
               prefixSum[x2 + 1, y1] + prefixSum[x1, y1];
      }

      int minLoss = int.MaxValue;
      int offset = radius - 1; // explosion range centered at (i,j) goes from i-offset to i+offset

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if (grid[i][j] == '.') { // Only explode on empty cells
            int x1 = Math.Max(0, i - offset);
            int y1 = Math.Max(0, j - offset);
            int x2 = Math.Min(rows - 1, i + offset);
            int y2 = Math.Min(cols - 1, j + offset);

            // This calculates gold that would be inside the explosion circle (strictly within)
            int lostGold = GetGoldInRegion(x1, y1, x2, y2);
            minLoss = Math.Min(minLoss, lostGold);
          }
        }
      }

      Console.WriteLine(totalGold - minLoss);
    }
  }
}


// https://github.com/VaHiX/codeForces/