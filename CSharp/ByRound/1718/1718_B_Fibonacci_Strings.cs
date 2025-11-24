// Problem: CF 1718 B - Fibonacci Strings
// https://codeforces.com/contest/1718/problem/B

﻿/*
 * Problem: Determine if a string is "semi-Fibonacci"
 * A string is semi-Fibonacci if its letters can be rearranged to form a Fibonacci string.
 * A Fibonacci string is one where block lengths (sequences of same characters) form the Fibonacci sequence.
 * 
 * Approach:
 * 1. Generate Fibonacci numbers up to a reasonable limit (60 terms is more than enough for 1e9 values)
 * 2. Check if the total number of characters in the string is one less than a Fibonacci number (f(n) = f(n-1) + f(n-2))
 * 3. If so, try to construct a valid sequence by greedily assigning character counts to Fibonacci numbers.
 * 
 * Time Complexity: O(k log k + 60) where k is the number of characters (due to sorting and generating Fibonacci sequence)
 * Space Complexity: O(1) for the actual algorithm, O(k) for storing input
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
    for (int hz = 0; hz < fyt; hz++) {
      var n = long.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      bool can = false;
      List<long> fi = new List<long>();
      fi.Add(1);
      fi.Add(1);
      for (int i = 0; i < 60; i++) {
        fi.Add(fi[fi.Count - 1] + fi[fi.Count - 2]);
      }
      long s = a.Sum();
      if (fi.Contains(s + 1)) {
        can = true;
        a = a.OrderByDescending(i => i).ToList();
        for (int id = fi.IndexOf(s + 1) - 2; id >= 0; id--) {
          a[0] -= fi[id];
          if (a[0] < 0 || (a.Count == 1 && a[0] > 0)) {
            can = false;
            break;
          }
          if (a.Count > 1 && a[0] > a[1]) {
            var t = a[0];
            a[0] = a[1];
            a[1] = t;
          } else
            a = a.OrderByDescending(i => i).ToList();
        }
      }
      if (can)
        output.Add("YES");
      else
        output.Add("NO");
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/