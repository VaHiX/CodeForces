// Problem: CF 1674 E - Breaking the Wall
// https://codeforces.com/contest/1674/problem/E

﻿/*
 * Problem: Breaking the Wall
 * Purpose: Find the minimum number of onager shots to break at least two sections of the wall.
 * 
 * Algorithm:
 * - Try all pairs of adjacent sections to break.
 * - Try all pairs of non-adjacent sections (with one gap).
 * - Try breaking the two weakest sections.
 * - For each scenario, calculate the minimal shots required based on damage distribution.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the number of sections.
 * Space Complexity: O(n) for storing the durability array and temporary lists.
 * 
 * Techniques:
 * - Greedy approach with case analysis on section pairs.
 * - Mathematical calculation for optimal shot numbers.
 * - Sorting to find minimum durability sections efficiently.
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      int o = int.MaxValue;
      // Check adjacent pairs for breaking
      for (int i = 0; i < n - 1; i++) {
        if ((a[i] + a[i + 1] + 2) / 3 < o) {
          // If the sum of two adjacent sections is sufficient to break both
          if (Math.Min(a[i], a[i + 1]) * 2 > Math.Max(a[i], a[i + 1]))
            o = (a[i] + a[i + 1] + 2) / 3;
          // Otherwise, the weaker section limits the number of shots needed
          else if ((Math.Max(a[i], a[i + 1]) + 1) / 2 < o)
            o = (Math.Max(a[i], a[i + 1]) + 1) / 2;
        }
      }
      // Check pairs with one section in between
      for (int i = 0; i < n - 2; i++) {
        if ((a[i] + a[i + 2] + 1) / 2 < o)
          o = (a[i] + a[i + 2] + 1) / 2;
      }
      // Check the two weakest sections
      a = a.OrderBy(i => i).ToList();
      if ((a[0] + 1) / 2 + (a[1] + 1) / 2 < o)
        o = (1 + a[0]) / 2 + (1 + a[1]) / 2;
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/