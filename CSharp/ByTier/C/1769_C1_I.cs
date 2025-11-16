// Problem: CF 1769 C1 - Подкрутка I
// https://codeforces.com/contest/1769/problem/C1

﻿/*
Algorithm: Dynamic Programming with State Tracking
Time Complexity: O(n) where n is the number of commits
Space Complexity: O(n) for the 2D DP array

This solution uses dynamic programming to track the optimal intervals 
for placing commits after possible adjustments (forward by at most one day).
The state tracks the earliest and latest positions for two possible
configurations of commit placements for the current day:
f[i,0] and f[i,1] represent the interval of commits that can be placed
in the current day or one day after, while f[i,2] and f[i,3] track
the other configuration.
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
      var n = long.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      int o = 0;
      int[,] f = new int[n, 4];
      // Initialize first commit's start and end positions for both configurations
      f[0, 0] = a[0];
      f[0, 1] = a[0];
      f[0, 2] = a[0] + 1;
      f[0, 3] = a[0] + 1;
      for (int i = 1; i < n; i++) {
        int c = a[i];
        // Calculate difference between current commit and previous configuration end
        int q = c - f[i - 1, 3];
        int q1 = f[i - 1, 1] - f[i - 1, 0]; // Length of first interval
        int q2 = f[i - 1, 3] - f[i - 1, 2]; // Length of second interval
        
        if (q == -1) {
          // Current commit is one day before previous interval end
          // Choose the configuration that minimizes gaps
          if (q1 >= q2) {
            f[i, 0] = f[i - 1, 0];
            f[i, 1] = f[i - 1, 1];
            f[i, 2] = f[i - 1, 0];
            f[i, 3] = f[i - 1, 1] + 1;
          } else {
            f[i, 0] = f[i - 1, 2];
            f[i, 1] = f[i - 1, 3];
            f[i, 2] = f[i - 1, 2];
            f[i, 3] = f[i - 1, 3];
          }
        } else if (q == 0) {
          // Current commit is at same day as previous interval end
          q1++;
          if (q1 >= q2) {
            f[i, 0] = f[i - 1, 0];
            f[i, 1] = f[i - 1, 1] + 1;
          } else {
            f[i, 0] = f[i - 1, 2];
            f[i, 1] = f[i - 1, 3];
          }
          f[i, 2] = f[i - 1, 2];
          f[i, 3] = f[i - 1, 3] + 1;
        } else if (q == 1) {
          // Current commit is one day after previous interval end
          f[i, 0] = f[i - 1, 2];
          f[i, 1] = a[i];
          f[i, 2] = a[i] + 1;
          f[i, 3] = a[i] + 1;
        } else {
          // Current commit is more than one day after previous interval end
          f[i, 0] = a[i];
          f[i, 1] = a[i];
          f[i, 2] = a[i] + 1;
          f[i, 3] = a[i] + 1;
        }
        // Keep the minimum positions for the intervals
        f[i, 1] = Math.Min(f[i, 1], a[i]);
        f[i, 3] = Math.Min(f[i, 3], a[i] + 1);
      }
      // Find maximum interval length from all configurations
      for (int i = 0; i < n; i++) {
        int q1 = f[i, 1] - f[i, 0];
        int q2 = f[i, 3] - f[i, 2];
        o = Math.Max(o, q1);
        o = Math.Max(o, q2);
      }
      o++;
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/