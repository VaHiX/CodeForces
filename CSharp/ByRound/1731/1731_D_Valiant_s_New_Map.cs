// Problem: CF 1731 D - Valiant's New Map
// https://codeforces.com/contest/1731/problem/D

/* 
 * Problem: Find the maximum side length of a square subgrid where all buildings have height >= side length.
 * 
 * Approach: Binary search on the answer combined with 2D prefix sums for efficient range sum queries.
 * 
 * Time Complexity: O(n * m * log(min(n, m))) where n and m are grid dimensions.
 * Space Complexity: O(n * m) for the prefix sum array.
 * 
 * Algorithms/Techniques:
 * - Binary Search on Answer: Search for the maximum valid square size.
 * - 2D Prefix Sum: For fast calculation of sum of elements in a subgrid.
 * 
 * Key Steps:
 * 1. For a given size 'l', use 2D prefix sums to check if any l x l square has all elements >= l.
 * 2. Binary search over possible square sizes.
 * 3. Prefix sum helps in checking validity of each square in O(1) after O(n*m) preprocessing.
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
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      int o = 0;
      long[][] d = new long[a[0]][];
      for (int i = 0; i < a[0]; i++) {
        d[i] = Console.ReadLine()
                   .Split(' ')
                   .Select(qw => long.Parse(qw))
                   .ToArray();
      }
      int l = 1;
      int r = a.Min(); // Binary search upper bound
      o = (l + r) / 2;
      int po = 1;
      int ss = 0; // Start row for next search to optimize (not used fully but part of logic)
      while (r - l >= 0) {
        // Precompute 2D prefix sum
        long[][] p = new long[a[0]][];
        for (int i = 0; i < a[0]; i++) {
          p[i] = new long[a[1]];
          long c = 0;
          for (int j = 0; j < a[1]; j++) {
            if (d[i][j] >= o) // Mark cells that satisfy condition
              c++;
            p[i][j] = c;
            if (i > 0)
              p[i][j] += p[i - 1][j]; // Add prefix sum from above row
          }
        }
        int s = o * o; // Total number of cells in square of size o
        bool can = false;
        // Check all possible o x o squares
        for (int i = Math.Max(ss, o - 1); i < a[0]; i++) { // Start from optimized row or o-1
          for (int j = o - 1; j < a[1]; j++) { // Start from column o-1
            long v = p[i][j]; // Sum of subgrid from (0,0) to (i,j)
            // Subtract top part if i >= o
            if (i >= o)
              v -= p[i - o][j];
            // Subtract left part if j >= o
            if (j >= o) {
              v -= p[i][j - o];
              // Add back the overlapping part if both i >= o and j >= o
              if (i >= o)
                v += p[i - o][j - o];
            }
            // If count equals total cells in square => all cells are >= o
            if (v == s) {
              ss = i;
              can = true;
              break;
            }
          }
          if (can)
            break;
        }
        // Update binary search range based on validity
        if (can) {
          po = o; // Store the valid answer
          l = o + 1; // Search for larger square
        } else {
          if (r == l)
            break;
          r = o - 1; // Search for smaller square
        }
        o = (l + r) / 2; // Next mid point
      }
      o = po; // Final answer
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/