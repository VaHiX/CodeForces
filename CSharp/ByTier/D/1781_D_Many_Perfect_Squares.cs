// Problem: CF 1781 D - Many Perfect Squares
// https://codeforces.com/contest/1781/problem/D

﻿/*
 * Problem: D. Many Perfect Squares
 * 
 * Purpose:
 *   Given a set of distinct positive integers, find the maximum number of perfect squares 
 *   that can be obtained by adding a non-negative integer x (0 ≤ x ≤ 10^18) to each element
 *   of the set. That is, maximize the count of perfect squares among:
 *   a1 + x, a2 + x, ..., an + x.
 * 
 * Algorithm:
 *   - For each pair (i, j) of elements in the set, compute their difference d = a[j] - a[i].
 *   - For every divisor k of d:
 *     - Compute p = k and q = d / k.
 *     - If (p + q) is even, compute e = (p + q) / 2.
 *     - Compute x = e^2 - a[j].
 *     - If x ≥ 0, store x in a dictionary with the indices i and j.
 *   - Group entries in dictionary by x and count unique indices for each x.
 *   - Return the maximum count of unique indices.
 * 
 * Time Complexity:
 *   O(n^2 * sqrt(D)) where n is the size of the array and D is the maximum difference
 *   between any two elements. The outer loop runs O(n^2) and for each difference d,
 *   we iterate up to sqrt(d), which is bounded by sqrt(10^9) ≈ 31623.
 * 
 * Space Complexity:
 *   O(n^2) due to storage of dictionary entries representing possible x values.
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < fyt; z++) {
      var n = int.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToArray();
      long o = 0;
      Dictionary<long, List<long>> d = new Dictionary<long, List<long>>();
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          long w = a[j] - a[i];  // Difference between elements
          for (int k = 1; k < Math.Sqrt(w + 1); k++) {
            if (w % k == 0) {  // k is a divisor of w
              long p = k;
              long q = w / k;
              if ((p + q) % 2 == 0) {  // Ensure sum is even (for integer e)
                long e = (p + q) / 2;  // e = (p + q) / 2
                long x = e * e - a[j];  // Compute candidate x
                if (x >= 0) {  // Only consider non-negative x
                  if (!d.ContainsKey(x))
                    d.Add(x, new List<long>());
                  d[x].Add(i);  // Store indices involved in formation
                  d[x].Add(j);
                }
              }
            }
          }
        }
      }
      d.ToList().ForEach(kv => {
        int yy = kv.Value.Distinct().Count();  // Count unique indices for each x
        if (yy > o)
          o = yy;
      });
      if (o < 1)
        o = 1;
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/