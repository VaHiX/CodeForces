// Problem: CF 1744 E1 - Divisible Numbers (easy version)
// https://codeforces.com/contest/1744/problem/E1

﻿/*
 * Problem: Find a pair (x, y) such that:
 *   - a < x <= c
 *   - b < y <= d
 *   - x * y is divisible by a * b
 *
 * Algorithm:
 *   1. Generate all divisors of a and b.
 *   2. For each pair of divisors (d1, d2) of a and b respectively:
 *       - Compute x = d1 * (a / d1) * k1, y = d2 * (b / d2) * k2 (where k1, k2 are chosen so that x <= c, y <= d)
 *       - Check if there exist valid x and y within the range.
 *   3. Return first valid pair found or -1 -1 if none exists.
 *
 * Time Complexity: O(sqrt(a) * sqrt(b) + sqrt(a) * sqrt(b)) = O(sqrt(a)*sqrt(b))
 * Space Complexity: O(sqrt(a) + sqrt(b)) for storing divisors
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
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      List<long> o = new List<long>();
      List<long> a1 = new List<long>() { 1, a[0] }; // Divisors of a
      List<long> a2 = new List<long>() { 1, a[1] }; // Divisors of b
      // Find all divisors of a
      for (int i = 2; i < Math.Sqrt(a[0] + 1); i++) {
        if (a[0] % i == 0) {
          a1.Add(i);
          if (i * i != a[0])
            a1.Add(a[0] / i);
        }
      }
      // Find all divisors of b
      for (int i = 2; i < Math.Sqrt(a[1] + 1); i++) {
        if (a[1] % i == 0) {
          a2.Add(i);
          if (i * i != a[1])
            a2.Add(a[1] / i);
        }
      }
      a1 = a1.OrderBy(i => i).ToList(); // Sort divisors of a
      a2 = a2.OrderBy(i => i).ToList(); // Sort divisors of b
      long x = -1;
      long y = -1;
      bool bro = false;
      // Iterate through all combinations of divisors
      for (int i = 0; i < a1.Count; i++) {
        for (int j = 0; j < a2.Count; j++) {
          var x1 = a1[i] * a2[j];
          var y1 = (a[0] / a1[i]) * (a[1] / a2[j]);
          // Adjust x1 and y1 to make them within valid range
          if (x1 <= a[0]) {
            x1 = x1 * (a[0] / x1 + 1); // Scale up x1 to exceed a
          }
          if (y1 <= a[1]) {
            y1 = y1 * (a[1] / y1 + 1); // Scale up y1 to exceed b
          }
          // Check if x1 and y1 are within the given limits
          if (x1 <= a[2] && y1 <= a[3]) {
            x = x1;
            y = y1;
            bro = true;
            break;
          }
        }
        if (bro)
          break;
      }
      o.Add(x);
      o.Add(y);
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/