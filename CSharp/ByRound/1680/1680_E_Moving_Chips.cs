// Problem: CF 1680 E - Moving Chips
// https://codeforces.com/contest/1680/problem/E

﻿/*
 * Problem: Moving Chips on a 2xN Board
 * 
 * Algorithm: Dynamic Programming with Forward and Backward Passes
 * 
 * Approach:
 * - We model the board as two rows of length n
 * - For each column, we calculate the minimum moves needed to collect all chips
 *   from the left (forward pass) and from the right (backward pass)
 * - Then we try all possible split points to combine the cost of collecting
 *   chips from both sides
 * 
 * Time Complexity: O(n) where n is the length of the board
 * Space Complexity: O(n) for the DP tables
 * 
 * Techniques:
 * - Forward and backward dynamic programming
 * - Cost calculation for chip movement
 * - Minimizing total moves by considering split points
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      Console.ReadLine();
      var s1 = Console.ReadLine();
      var s2 = Console.ReadLine();
      int[,] lr = new int[s1.Length, 2]; // Forward pass DP: lr[i,0] = cost to collect from left to i (at row 1), lr[i,1] = row 2
      int[,] rl = new int[s1.Length, 2]; // Backward pass DP: rl[i,0] = cost to collect from right to i (at row 1), rl[i,1] = row 2
      
      // Initialize base cases
      if (s1[0] == '*')
        lr[0, 1] = 1; // Start at row 1, col 0
      if (s2[0] == '*')
        lr[0, 0] = 1; // Start at row 2, col 0
      if (s1.Last() == '*')
        rl[s1.Length - 1, 1] = 1; // Start at row 1, last col
      if (s2.Last() == '*')
        rl[s1.Length - 1, 0] = 1; // Start at row 2, last col

      // Forward pass: compute cost to collect chips from left to right
      for (int i = 1; i < s1.Length; i++) {
        if (lr[i - 1, 0] == 0 && s1[i - 1] == '.') { // Previous cell is empty in row 1, so we don't have any chip in that row yet
          // If we're in a new region from previous col, we can start collecting from current position
          if (s2[i] == '*') // Chip exists in row 2 at current column
            lr[i, 0] = 1; // One step to move to this position (0 cost of collecting)
          if (s1[i] == '*')
            lr[i, 1] = 1; // Similarly for row 1
          if (s2[i - 1] == '*') // Previous cell in row 2 also has chip
            lr[i, 1]++; // Add a cost for moving there (collecting)
          if (s1[i - 1] == '*') // Previous cell in row 1 also has chip
            lr[i, 0]++; // Add a cost for moving there
        } else {
          // If we already have a chip in the region from previous column, we update costs based on available paths
          if (s2[i] == '*') // If there's a chip in row 2 in current column, we can move from previous column
            lr[i, 0] = Math.Min(lr[i - 1, 0] + 2, lr[i - 1, 1] + 2); // Cost to move to row 2
          else
            lr[i, 0] = Math.Min(lr[i - 1, 0] + 1, lr[i - 1, 1] + 2); // Cost to move to row 2 (1 step)
          if (s1[i] == '*') // Similarly for row 1
            lr[i, 1] = Math.Min(lr[i - 1, 1] + 2, lr[i - 1, 0] + 2); // Cost to move to row 1
          else
            lr[i, 1] = Math.Min(lr[i - 1, 1] + 1, lr[i - 1, 0] + 2); // Cost to move to row 1 (1 step)
        }
      }
      
      // Backward pass: compute cost to collect chips from right to left
      for (int i = s1.Length - 2; i >= 0; i--) {
        if (rl[i + 1, 0] == 0 && s1[i + 1] == '.') {
          // Similar logic as forward pass, but in reverse direction
          if (s2[i] == '*')
            rl[i, 0] = 1;
          if (s1[i] == '*')
            rl[i, 1] = 1;
          if (s1[i + 1] == '*')
            rl[i, 0]++;
          if (s2[i + 1] == '*')
            rl[i, 1]++;
        } else {
          // Same as forward pass, but for backtracking
          if (s2[i] == '*')
            rl[i, 0] = Math.Min(rl[i + 1, 0] + 2, rl[i + 1, 1] + 2);
          else
            rl[i, 0] = Math.Min(rl[i + 1, 0] + 1, rl[i + 1, 1] + 2);
          if (s1[i] == '*')
            rl[i, 1] = Math.Min(rl[i + 1, 1] + 2, rl[i + 1, 0] + 2);
          else
            rl[i, 1] = Math.Min(rl[i + 1, 1] + 1, rl[i + 1, 0] + 2);
        }
      }
      
      // Find minimum cost to keep one chip at any single position
      long o = Math.Min(Math.Min(rl[0, 0], rl[0, 1]),
                        Math.Min(lr[s1.Length - 1, 0], lr[s1.Length - 1, 1]));
      
      // Try to split the board and calculate minimal costs for combining left and right sections
      for (int i = 0; i < s1.Length - 1; i++) {
        int t = 0;
        if ((lr[i, 0] > 0 || s1[i] == '*') && // If we can reach row 1 at column i
            (rl[i + 1, 0] > 0 || s1[i + 1] == '*')) // or if we can reach row 1 at column i+1
          t = 1; // Add cost of one move to "capture" the chip if not already covered
        
        // Calculate combination cost for this split
        if (lr[i, 0] + rl[i + 1, 0] + t < o) {
          o = lr[i, 0] + rl[i + 1, 0] + t;
        }
        t = 0;
        // Same logic but for row 2
        if ((lr[i, 1] > 0 || s2[i] == '*') &&
            (rl[i + 1, 1] > 0 || s2[i + 1] == '*'))
          t = 1;
        if (lr[i, 1] + rl[i + 1, 1] + t < o) {
          o = lr[i, 1] + rl[i + 1, 1] + t;
        }
      }
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/