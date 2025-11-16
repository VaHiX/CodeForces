// Problem: CF 1740 C - Bricks and Bags
// https://codeforces.com/contest/1740/problem/C

﻿/*
 * Problem: C. Bricks and Bags
 * 
 * Algorithm/Technique: 
 * - The goal is to distribute n bricks into 3 bags such that the maximum possible score is achieved,
 *   where the score is calculated as |w1 - w2| + |w2 - w3|, with wj being the weight of the brick
 *   taken from bag j by Bu Dengklek, who minimizes the score.
 * - Key insight: After sorting the brick weights, the optimal distribution can be analyzed by
 *   considering splits on sorted weights and checking the score for those configurations.
 * - The solution uses a greedy approach over the sorted distinct weights to find the maximum possible
 *   score by considering splits that maximize the difference between adjacent elements and 
 *   accounting for the overall spread of the weights.
 * 
 * Time Complexity: O(n log n) due to sorting operations, where n is the number of bricks.
 * Space Complexity: O(n) for storing and processing the brick weights.
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
      var n = int.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      long o = 0;
      // Remove duplicates and sort the weights
      a = a.Distinct().OrderBy(i => i).ToList();
      long m = a.First(); // Smallest weight
      n = a.Count;
      long l = a.Last();  // Largest weight
      long f = m;
      // Iterating through sorted weights to find the maximum difference
      for (int i = 0; i < n - 1; i++) {
        long d = a[i + 1] - a[i] - (a[i] - f); // Compute a potential max score
        if (d > o)
          o = d;
      }
      m = l;
      // Reverse iteration through sorted weights to find another max score
      for (int i = n - 1; i > 0; i--) {
        long d = a[i] - a[i - 1] - (l - a[i]); // Compute another potential max score
        if (d > o)
          o = d;
      }
      o += l - f; // Add the total spread of the weights
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/