// Problem: CF 2051 A - Preparing for the Olympiad
// https://codeforces.com/contest/2051/problem/A

﻿/*
 * Problem: A. Preparing for the Olympiad
 * 
 * Description:
 * Monocarp and Stereocarp are preparing for an Olympiad with n days left.
 * On day i:
 * - Monocarp solves a[i] problems if he trains.
 * - Stereocarp solves b[i] problems if he trains.
 * 
 * Stereocarp follows Monocarp's schedule: if Monocarp trains on day i (where i < n),
 * then Stereocarp trains on day i+1. If Monocarp doesn't train, Stereocarp doesn't train either.
 * 
 * Goal: Maximize the difference (Monocarp's total - Stereocarp's total).
 * 
 * Algorithm:
 * Greedily decide at each step whether to train or not:
 * For each day i, compare:
 *   - Not training: difference remains same
 *   - Training: Monocarp gains a[i] and Stereocarp gains b[i+1] (if exists)
 * We use prefix sums to track totals and update the maximum difference accordingly.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) extra space
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Net.Sockets;

namespace 最新版琦呀哩的编程 {
internal class Program {
  static void Main(string[] args) {
    int n = int.Parse(Console.ReadLine());
    for (int i = 0; i < n; i++) {
      int times = int.Parse(Console.ReadLine());
      int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
      int[] b = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
      int monoproblem = 0;
      int stereproblem = 0;
      int differenceiftrain = 0;
      int differenceifnottrain = 0;
      int maxproblem = 0;
      for (int j = 0; j < times; j++) {
        int monotrain = a[j];
        int steretrain = 0;
        if (j < times - 1) { // Stereocarp trains on next day if Monocarp trains today
          steretrain = b[j + 1];
        }
        // Calculate difference WITHOUT training on current day
        differenceifnottrain = monoproblem - stereproblem;
        // Calculate difference WITH training on current day
        differenceiftrain =
            (monoproblem + monotrain) - (stereproblem + steretrain);
        if (differenceiftrain > differenceifnottrain) {
          // Decision: Train today to increase the difference
          monoproblem += monotrain;
          stereproblem += steretrain;
          maxproblem = Math.Max(maxproblem, differenceiftrain);
        } else {
          // Decision: Do not train today
          maxproblem = Math.Max(maxproblem, differenceifnottrain);
        }
      }
      Console.WriteLine(maxproblem);
    }
  }
}
}


// https://github.com/VaHiX/codeForces/