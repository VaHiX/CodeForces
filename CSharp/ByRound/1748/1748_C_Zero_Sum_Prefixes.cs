// Problem: CF 1748 C - Zero-Sum Prefixes
// https://codeforces.com/contest/1748/problem/C

﻿/*
Algorithm: Zero-Sum Prefixes
Approach:
- We iterate through the array and maintain a prefix sum.
- When we encounter a zero, we can change its value to make prefix sums equal to zero at that point.
- We use a dictionary to store counts of each prefix sum encountered so far.
- If a prefix sum has been seen before, it means there's a subarray with sum zero.
- The key insight is to maximize the number of zero prefix sums by adjusting zeros appropriately.

Time Complexity: O(n), where n is the length of the array. Each element is processed once.
Space Complexity: O(n), for storing prefix sums and the dictionary.
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
      long o = 0; // Final score to be calculated
      long[] s = new long[n + 1]; // Prefix sum array
      for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i - 1]; // Compute prefix sums
      }
      Dictionary<long, int> b = new Dictionary<long, int>(); // Stores count of prefix sums
      bool had0 = false; // Tracks if we have seen a zero so far
      for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
          // If we've already seen a zero, we can add the maximum count of previous prefix sums
          if (had0) {
            var v = b.Values;
            if (v.Count > 0)
              o += v.Max();
          } else {
            // If no zero encountered yet, check if prefix sum 0 exists
            if (b.ContainsKey(0))
              o += b[0];
          }
          b = new Dictionary<long, int>(); // Reset dictionary for next section
          b.Add(s[i + 1], 1); // Add the next prefix sum
          had0 = true; // Mark that we've seen a zero
        } else {
          // For non-zero elements, just add the prefix sum to dictionary
          if (!b.ContainsKey(s[i + 1]))
            b.Add(s[i + 1], 1);
          else
            b[s[i + 1]]++;
        }
      }
      // After processing all elements, if had0 is true, add max count in dictionary
      if (had0) {
        var v = b.Values;
        if (v.Count > 0)
          o += v.Max();
      } else {
        // If no zero was encountered, check if prefix sum 0 exists
        if (b.ContainsKey(0))
          o += b[0];
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/