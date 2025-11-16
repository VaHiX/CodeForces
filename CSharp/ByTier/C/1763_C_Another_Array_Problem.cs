// Problem: CF 1763 C - Another Array Problem
// https://codeforces.com/contest/1763/problem/C

﻿/*
 * Problem: Another Array Problem
 * 
 * Algorithm:
 * - The key insight is to determine the maximum possible sum after applying operations.
 * - Each operation replaces a subarray [i, j] with |a[i] - a[j]|, which essentially replaces 
 *   all elements in the range with the absolute difference of the first and last elements of that range.
 * - We analyze different cases based on the size of the array:
 *   - For n = 2: We can either keep the original sum or perform one operation to get 2 * |a[0] - a[1]|.
 *   - For n >= 4: We can always force the whole array to become the maximum element, so the answer is n * max_element.
 *   - For n = 3: We consider multiple strategies, like using a single operation to maximize sum.
 * 
 * Time Complexity: O(n) per test case due to linear operations (sum, max, etc.)
 * Space Complexity: O(n) for storing the input array and output
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
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 0;
      if (n == 2) {
        // For n=2, either keep original sum or perform one operation to get 2 * |a[0] - a[1]|
        o = Math.Max(a.Sum(), 2 * (a.Max() - a.Min()));
      } else if (n >= 4) {
        // For n >= 4, we can ensure all elements become the maximum value
        o = a.Count * a.Max();
      } else {
        // For n = 3, consider all possible operations carefully
        o = a.Sum();
        if (a[0] == a.Max() || a[2] == a.Max()) {
          // If either first or last element is maximum, set entire array to max
          o = 3 * a.Max();
        } else {
          // Otherwise, evaluate all possible 3-element combinations and operations
          o = Math.Max(o, 3 * a[0]); // Keep first element max
          o = Math.Max(o, 3 * a[2]); // Keep last element max
          o = Math.Max(o, a[0] + 2 * Math.Abs(a[2] - a[1])); // Operation on 0..2
          o = Math.Max(o, a[2] + 2 * Math.Abs(a[0] - a[1])); // Operation on 0..2 (reverse)
          o = Math.Max(o, 3 * Math.Abs(a[0] - a[1])); // Operation on 0..1
          o = Math.Max(o, 3 * Math.Abs(a[2] - a[1])); // Operation on 1..2
        }
      }
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/