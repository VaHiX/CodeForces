// Problem: CF 1715 C - Monoblock
// https://codeforces.com/contest/1715/problem/C

﻿/*
 * Problem: Monoblock
 * Purpose: Calculate the sum of awesomeness values for all subsegments of an array after each update query.
 * 
 * Algorithm:
 * - Precompute initial sum of awesomeness for all subsegments using mathematical formula.
 * - For each query, efficiently update the total sum by recalculating changes in awesomeness
 *   only at positions affected by the change.
 * 
 * Complexity:
 * - Time: O(n^2 + m*n) where n is array size and m is number of queries
 * - Space: O(n) for storing the array
 * 
 * Techniques:
 * - Mathematical precomputation
 * - Efficient updates by tracking changes in consecutive blocks
 */
using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < fyt; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToArray();
      var b =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToArray();
      long o = 0;
      long n = a[0];
      // Precompute initial sum of all awesomeness values using formula
      o = (n * n * n + 3 * n * n + 2 * n) / 6;
      // Subtract contributions from consecutive equal elements
      for (int i = 1; i < n; i++) {
        if (b[i] == b[i - 1]) {
          o -= (i) * (n - i);
        }
      }
      for (int k = 0; k < a[1]; k++) {
        var c = Console.ReadLine()
                    .Split(' ')
                    .Select(qw => long.Parse(qw))
                    .ToArray();
        long v = c[1];
        int p = (int)(c[0] - 1); // Convert to 0-based index
        // Check if previous element is same and adjust sum accordingly
        if (p > 0 && b[p] == b[p - 1])
          o += p * (n - p);
        // Check if next element is same and adjust sum accordingly
        if (p < n - 1 && b[p] == b[p + 1])
          o += (p + 1) * (n - p - 1);
        // Update the array element
        b[p] = v;
        // Check if previous element is same and adjust sum accordingly
        if (p > 0 && b[p] == b[p - 1])
          o -= p * (n - p);
        // Check if next element is same and adjust sum accordingly
        if (p < n - 1 && b[p] == b[p + 1])
          o -= (p + 1) * (n - p - 1);
        output.Add(o.ToString());
      }
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/