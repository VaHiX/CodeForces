// Problem: CF 1901 B - Chip and Ribbon
// https://codeforces.com/contest/1901/problem/B

/*
 * Chip and Ribbon Problem
 * 
 * Purpose:
 *   This program calculates the minimum number of times a chip needs to be teleported 
 *   to achieve a desired integer configuration on a ribbon of cells. The chip moves 
 *   sequentially through cells and can be teleported to any cell. At each cell, the value 
 *   increases by 1 each time the chip is there.
 * 
 * Algorithms/Techniques:
 *   - Sorting and grouping elements by their values.
 *   - Two-pointer technique with a sliding window approach to determine 
 *     where teleports are needed.
 *   - Efficient tracking of critical transitions using a boolean array to mark 
 *     which positions are occupied.
 * 
 * Time Complexity:
 *   O(n log n) due to sorting, where n is the number of cells.
 *   
 * Space Complexity:
 *   O(n) for storing the input values, indices, and auxiliary arrays.
 */

using System;

public class ChipAndRibbon {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] c = new int[n];
      int[] idxs = new int[n];
      for (int j = 0; j < n; j++) {
        c[j] = int.Parse(parts[j]);
        idxs[j] = j;
      }
      // Sort the values and maintain original indices
      Array.Sort(c, idxs);
      
      // Initialize result with the maximum value minus 1 (minimum teleports for first step)
      long ans = c[n - 1] - 1;
      
      // Track occupied cells
      bool[] walls = new bool[n];
      
      int l = 0;
      int r = 1;
      int countWall = 0; // Number of walls that need to be crossed (i.e., teleport needed)
      int cPrev = 0; // Previous value in sorted array
      while (l < n) {
        // Advance r pointer to group all same values
        while (r < n && c[r] == c[l])
          r++;
        
        // Add the cost of moving from cPrev to c[l] for all currently active positions
        ans += (c[l] - cPrev) * (long)countWall;
        cPrev = c[l];
        
        // Process all positions with value c[l]
        while (l < r) {
          int idx = idxs[l];
          // If this position is internal (not on edge) and both neighbors are not walls,
          // we need to count this as a potential wall crossing
          if (idx > 0 && idx < n - 1 && !walls[idx - 1] && !walls[idx + 1])
            countWall++;
          // If this is an edge or both neighbors are already walls, it may reduce the count
          else if (n > 1 &&
                   (idx == 0 && walls[1] || idx == n - 1 && walls[n - 2] ||
                    idx > 0 && idx < n - 1 && walls[idx - 1] && walls[idx + 1]))
            countWall--;
          walls[idx] = true;
          l++;
        }
        r = l + 1;
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/