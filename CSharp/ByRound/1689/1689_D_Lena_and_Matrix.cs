// Problem: CF 1689 D - Lena and Matrix
// https://codeforces.com/contest/1689/problem/D

/* 
 * Problem: Lena and Matrix
 * Algorithm: Distance calculation using dynamic programming approach
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for the DP tables
 * 
 * The solution uses a two-phase dynamic programming approach:
 * 1. First pass (top-left to bottom-right): computes minimum distance to nearest black cell in top and left directions
 * 2. Second pass (bottom-right to top-left): computes minimum distance to nearest black cell in bottom and right directions
 * Finally, the optimal cell is chosen as the one that minimizes the maximum of these two distances.
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
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      List<string> data = new List<string>();
      for (int i = 0; i < a[0]; i++) {
        string s = Console.ReadLine();
        data.Add(s);
      }
      int[,] v = new int[a[0], a[1]]; // DP table for first pass
      int[,] v2 = new int[a[0], a[1]]; // DP table for second pass
      for (int i = 0; i < a[0]; i++) {
        int q = -1;
        for (int j = 0; j < a[1]; j++) {
          v[i, j] = -1;
          // If we have a value from the cell above, we increment it
          if (i > 0 && v[i - 1, j] >= 0)
            v[i, j] = v[i - 1, j] + 1;
          // If the current cell is black, we reset the counter to 0
          if (data[i][j] == 'B' && q == -1)
            q = 0;
          // If we have a value from the left side, we update v[i,j] if it's smaller
          if (v[i, j] < q)
            v[i, j] = q;
          // Increment the counter for the next iteration
          if (q >= 0)
            q++;
        }
        q = -1;
        // Reverse pass from right to left
        for (int j = (int)a[1] - 1; j >= 0; j--) {
          // If the current cell is black, we reset the counter to 0
          if (data[i][j] == 'B' && q == -1)
            q = 0;
          // If we have a value from the right side, we update v[i,j] if it's smaller
          if (v[i, j] < q)
            v[i, j] = q;
          // Increment the counter for the next iteration
          if (q >= 0)
            q++;
        }
      }
      for (int i = (int)a[0] - 1; i >= 0; i--) {
        int q = -1;
        for (int j = 0; j < a[1]; j++) {
          v2[i, j] = -1;
          // If we have a value from the cell below, we increment it
          if (i < a[0] - 1 && v2[i + 1, j] >= 0)
            v2[i, j] = v2[i + 1, j] + 1;
          // If the current cell is black, we reset the counter to 0
          if (data[i][j] == 'B' && q == -1)
            q = 0;
          // If we have a value from the bottom side, we update v2[i,j] if it's smaller
          if (v2[i, j] < q)
            v2[i, j] = q;
          // Increment the counter for the next iteration
          if (q >= 0)
            q++;
        }
        q = -1;
        // Reverse pass from right to left
        for (int j = (int)a[1] - 1; j >= 0; j--) {
          // If the current cell is black, we reset the counter to 0
          if (data[i][j] == 'B' && q == -1)
            q = 0;
          // If we have a value from the right side, we update v2[i,j] if it's smaller
          if (v2[i, j] < q)
            v2[i, j] = q;
          // Increment the counter for the next iteration
          if (q >= 0)
            q++;
        }
      }
      int bv = int.MaxValue;
      int bx = 0;
      int by = 0;
      // Find the cell that minimizes max distance to all black cells
      for (int i = 0; i < a[0]; i++) {
        for (int j = 0; j < a[1]; j++) {
          // Take the maximum of both passes
          if (Math.Max(v[i, j], v2[i, j]) < bv) {
            bv = Math.Max(v[i, j], v2[i, j]);
            bx = i;
            by = j;
          }
        }
      }
      output.Add((bx + 1).ToString() + " " + (by + 1).ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/