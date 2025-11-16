// Problem: CF 1749 D - Counting Arrays
// https://codeforces.com/contest/1749/problem/D

﻿/*
 * Code Purpose: Calculate the number of ambiguous arrays of length 1 to n,
 * where each element is between 1 and m. An ambiguous array has at least two
 * different removal sequences.
 * 
 * Algorithm: This implementation uses inclusion-exclusion principle combined
 * with mathematical properties of GCD and prime factorization to count valid arrays.
 * 
 * Time Complexity: O(n * log(n)) due to prime factor calculations and loops.
 * Space Complexity: O(1) as only a few variables are used.
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
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 1;
      long o3 = 0;
      // Calculate total arrays without restrictions
      for (int i = 0; i < a[0]; i++) {
        o *= (a[1] % 998244353);
        o %= 998244353;
        o3 += o;
        o3 %= 998244353;
      }
      o = o3;
      long o1 = a[1] % 998244353;
      long t = 30;
      long o2 = o1;
      // Calculate ambiguous arrays using inclusion-exclusion principle
      for (int i = 2; i <= a[0]; i++) {
        if (i == 2)
          o1 *= (a[1] / 2) % 998244353;
        else if (i < 5)
          o1 *= (a[1] / 6) % 998244353;
        else if (i < 7)
          o1 *= (a[1] / 30) % 998244353;
        else if (i < 11)
          o1 *= (a[1] / (t * 7)) % 998244353;
        else if (i < 13)
          o1 *= (a[1] / (t * 7 * 11)) % 998244353;
        else if (i < 17)
          o1 *= (a[1] / (t * 7 * 11 * 13)) % 998244353;
        else if (i < 19)
          o1 *= (a[1] / (t * 7 * 11 * 13 * 17)) % 998244353;
        else if (i < 23)
          o1 *= (a[1] / (t * 7 * 11 * 13 * 17 * 19)) % 998244353;
        else if (i < 29)
          o1 *= (a[1] / (t * 7 * 11 * 13 * 17 * 23 * 19)) % 998244353;
        else if (i < 31)
          o1 *= (a[1] / (t * 7 * 11 * 13 * 17 * 23 * 29 * 19)) % 998244353;
        else if (i < 37)
          o1 *= (a[1] / (t * 7 * 11 * 13 * 17 * 23 * 29 * 31 * 19)) % 998244353;
        else if (i < 41)
          o1 *= (a[1] / (t * 7 * 11 * 13 * 17 * 23 * 29 * 31 * 37 * 19)) %
                998244353;
        o1 %= 998244353;
        o2 += o1;
        o2 %= 998244353;
      }
      // Final result: total - ambiguous arrays (mod 998244353)
      o += 998244353;
      o -= o2;
      o %= 998244353;
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/