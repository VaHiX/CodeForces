// Problem: CF 1783 E - Game of the Year
// https://codeforces.com/contest/1783/problem/E

﻿// Purpose: Determine all values of k from 1 to n such that Monocarp kills all bosses in a game.
// Algorithm: 
//   1. For each boss, calculate the range of k values where Polycarp kills it before Monocarp.
//   2. Merge overlapping ranges to avoid double counting.
//   3. For each k from 1 to n, check if there exists any boss where k is in a forbidden range.
// Time Complexity: O(n log n) due to sorting and processing ranges
// Space Complexity: O(n) for storing ranges and boolean array

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < fyt; z++) {
      var n = int.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      List<int> o = new List<int>();
      int min = 1;
      int max = n;
      List<int[]> c = new List<int[]>((int)n + 1);
      // Calculate ranges where Polycarp kills the boss before Monocarp
      for (int i = 0; i < n; i++)
        if (b[i] < a[i])
          c.Add(new int[2] { b[i], a[i] - 1 });
      bool[] incl = new bool[n + 1];
      if (c.Count > 0) {
        c = c.OrderBy(i => i[0]).ToList();
        int ls = c[0][0];
        int lf = c[0][0];
        // Mark all k values in range [c[0][0], c[0][1]] as forbidden
        for (int k = c[0][1]; k >= c[0][0]; k--) {
          incl[k] = true;
        }
        for (int i = 1; i < c.Count; i++) {
          if (c[i][0] <= lf) {
            // Overlapping ranges: merge them
            for (int k = c[i][1]; k >= c[i - 1][1]; k--) {
              incl[k] = true;
            }
            lf = Math.Max(c[i - 1][1], c[i][1]);
            c[i - 1][1] = lf;
            c[i][0] = c[i - 1][0];
            c[i][1] = c[i - 1][1];
          } else {
            // Non-overlapping range
            lf = c[i][1];
            for (int k = c[i][1]; k >= c[i][0]; k--) {
              incl[k] = true;
            }
          }
        }
      }
      // Check all k from 1 to n to see if Monocarp can kill all bosses
      for (int i = 1; i <= n; i++) {
        bool broken = false;
        // Check multiples of i (k, 2k, 3k, ...) to see if any is forbidden
        for (int k = i; k <= n; k += i) {
          if (incl[k]) {
            broken = true;
            break;
          }
        }
        if (!broken)
          o.Add(i);
      }
      output.Add(o.Count.ToString());
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/