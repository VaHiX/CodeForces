// Problem: CF 1680 C - Binary String
// https://codeforces.com/contest/1680/problem/C

﻿/*
 * Problem: Binary String
 * Algorithm: Two-pointer technique with sliding window
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(1) - only using a constant amount of extra space
 *
 * The approach uses two pointers to simulate removing characters from both ends.
 * We maintain counts of 0s and 1s in the remaining string and compute the cost as
 * max(count of 0s left, count of 1s removed). We iterate through all possible
 * valid removal combinations to find the minimum cost.
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
      var s = Console.ReadLine();
      long o = 0;
      o = s.Where(i => i == '1').Count(); // Count total number of 1s
      int c0 = 0; // Count of 0s in the remaining string
      int c1 = (int)o; // Count of 1s in the remaining string
      int l = 0; // Left pointer (characters removed from beginning)
      int r = 0; // Right pointer (characters removed from end)
      while (l < s.Length || c1 < c0) {
        // If we should move the right pointer (either because we're at the start or there are more 1s than 0s in the remaining part)
        if ((c1 > c0 || l == r) && r < s.Length) {
          r++; // Move right pointer
          if (s[r - 1] == '1')
            c1--; // If the character added to the right side is 1, decrease the count of 1s
          else
            c0++; // If the character added to the right side is 0, increase the count of 0s
          if (o > Math.Max(c1, c0)) // Update minimum cost if current cost is smaller
            o = Math.Max(c1, c0);
        } else {
          l++; // Move left pointer
          if (s[l - 1] == '1')
            c1++; // If the character removed from the left side is 1, increase the count of 1s in the remaining string
          else
            c0--; // If the character removed from the left side is 0, decrease the count of 0s in the remaining string
          if (o > Math.Max(c1, c0)) // Update minimum cost if current cost is smaller
            o = Math.Max(c1, c0);
        }
      }
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/