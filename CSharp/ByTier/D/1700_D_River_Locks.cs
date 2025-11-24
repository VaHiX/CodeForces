// Problem: CF 1700 D - River Locks
// https://codeforces.com/contest/1700/problem/D

/*
 * Problem: River Locks
 * 
 * Algorithm/Techniques: 
 * - Preprocessing to calculate prefix sums and cumulative water levels
 * - Binary search or two-pointer technique to determine minimum pipes needed
 * - For each query, determine the minimum number of pipes such that all locks 
 *   can be filled within t seconds by simulating water flow through the system.
 * 
 * Time Complexity: O(n log n + q log q)
 * Space Complexity: O(n + q)
 * 
 * Approach:
 * - Preprocess the volumes to compute prefix sums and determine cumulative water dynamics
 * - For each query, use a two-pointer technique to find the minimum number of pipes required
 * - The solution determines when each lock can be filled, considering overflow to subsequent locks
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
      var b =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long[] a = new long[n]; // prefix sum array
      long[] k = new long[n]; // k[i] = water level at lock i after i seconds
      long[] c = new long[n]; // c[i] = minimum time to fill all locks up to i
      long q = 0;
      for (int i = 0; i < n; i++) {
        q += b[i];
        a[i] = q;
      }
      long su = a[n - 1]; // total volume
      c[0] = su;
      k[0] = a[0];
      for (int i = 1; i < n; i++) {
        // Calculate how much water can accumulate at lock i
        k[i] = k[i - 1] +
               Math.Max(0, (b[i] - k[i - 1] + (a[i - 1] - k[i - 1] * i) + i)) /
                   (i + 1);
        // Calculate minimum time needed to fill all locks from 0 to i
        c[i] = k[i] +
               Math.Max(0, su - a[i] + (a[i] - k[i] * (i + 1)) + i) / (i + 1);
      }
      var ql = int.Parse(Console.ReadLine());
      List<long[]> w = new List<long[]>(ql);
      for (int i = 0; i < ql; i++) {
        w.Add(new long[3] { i, long.Parse(Console.ReadLine()), 0 }); // {index, time, result}
      }
      w = w.OrderByDescending(m => m[1]).ToList(); // Sort queries by time descending
      int l = 0;
      int r = 0;
      while (r < w.Count) {
        if (w[r][1] >= c[l]) {
          w[r][2] = l + 1;
          r++;
        } else {
          if (l >= c.Length - 1) {
            w[r][2] = -1; // Impossible to fill all locks
            r++;
          } else
            l++;
        }
      }
      w.OrderBy(m => m[0]).ToList().ForEach(m => Console.WriteLine(m[2]));
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/