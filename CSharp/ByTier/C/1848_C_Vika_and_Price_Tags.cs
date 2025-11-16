// Problem: CF 1848 C - Vika and Price Tags
// https://codeforces.com/contest/1848/problem/C

﻿/*
 * Problem: Vika and Price Tags
 * Purpose: Determine if a pair of arrays becomes dull (all elements in array 'a' become zero after repeated operations).
 * Algorithm: 
 *   - For each pair of elements (a[i], b[i]), compute the number of steps until the first element becomes zero.
 *   - Use a recursive function to simulate the GCD-like process with modulo operations.
 *   - Check if all resulting step counts (mod 3) are the same.
 * 
 * Time Complexity: O(n * log(max(a[i], b[i]))) per test case, where n is the array size.
 * Space Complexity: O(n) for storing the step counts modulo 3.
 */

using System;
using System.Linq;
using System.Collections.Generic;
namespace ProblemC {
internal class ProblemC {
  // Function to calculate steps until one of the numbers becomes zero
  private static int StepsUntilZero(int a, int b) {
    if (a == 0) {
      return 0;
    }
    if (b == 0) {
      return 0;
    }
    if (a <= b) {
      return StepsUntilZero(b, b - a) + 1;
    }
    var k = a / (b * 2);
    if (k == 0) {
      return StepsUntilZero(b, a - b) + 1;
    }
    var residue = a - b * 2 * k;
    if (residue == 0) {
      return k * 3 - 1;
    }
    return k * 3 + StepsUntilZero(residue, b);
  }
  
  // Optimized version of StepsUntilZero
  private static int StepsUntilZero2(int a, int b) {
    if (a == 0) {
      return 0;
    }
    if (b == 0) {
      return 1;
    }
    if (a <= b) {
      return StepsUntilZero2(b, b - a) + 1;
    }
    var k = a / b;
    var r = a % b;
    if (k % 2 == 1) {
      return StepsUntilZero2(b, r) + k + k / 2;
    }
    return StepsUntilZero2(r, b) + k + k / 2;
  }
  
  public static void Main(string[] args) {
    var t = int.Parse(Console.ReadLine());
    for (var tt = 0; tt < t; ++tt) {
      var n = int.Parse(Console.ReadLine());
      var a = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
      var b = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
      var c = new List<int>();
      for (var i = 0; i < n; ++i) {
        if (a[i] == 0 && b[i] == 0) {
          continue; // Skip pairs that are already zero
        }
        c.Add(StepsUntilZero2(a[i], b[i]) % 3); // Store mod 3 result for each pair
      }
      if (c.Distinct().Count() <= 1) {
        Console.WriteLine("YES"); // All have same pattern -> dull
      } else {
        Console.WriteLine("NO"); // Different patterns -> not dull
      }
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/