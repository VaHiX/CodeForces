// Problem: CF 1759 F - All Possible Digits
// https://codeforces.com/contest/1759/problem/F

﻿/*
 * Problem: All Possible Digits
 * 
 * Algorithm: 
 * - We need to find the minimum number of operations to make all digits from 0 to p-1 appear in the number.
 * - The key insight is that when we increment the number, we can potentially introduce new digits.
 * - The solution involves working with the current digits and calculating how much we need to increment before all digits 0..p-1 are present.
 * 
 * Time Complexity: O(n log n) per test case due to sorting and processing of digits
 * Space Complexity: O(n) for storing the digits
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
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      long o = 0;
      int n = a[0];
      int p = a[1];
      var c = b.Distinct().OrderBy(i => i).ToList(); // Get distinct digits and sort them
      if (c.Count < p) { // If we don't have all digits yet
        int l = 0;
        if (c[0] == 0) { // If we already have 0
          int r = 0;
          bool broken = false;
          for (int i = 1; i < c.Count(); i++) {
            if (c[i] == r + 1) { // Check for consecutive digits
              r = c[i];
            } else if (c[i] > 0) { // Found a gap
              l = c[i - 1] + 1; // Start of gap
              broken = true;
              break;
            }
          }
          if (!broken) {
            if (c.Last() < p - 1) // If we are missing some higher digits
              l = c.Last() + 1; // Start from the last digit + 1
          }
        }
        if (l < b[n - 1]) { // Compare with last digit of current number
          var d = c.ToList();
          int q = b[n - 1]; // Store the last digit
          b[n - 1] = p; // Set last digit to base p to trigger carry
          int k = 0;
          for (int j = n - 1; j >= 0; j--) {
            if (b[j] == p) { // Handle carry
              if (j == 0) {
                b.Insert(0, 0);
                n++;
                j++;
              }
              b[j] = 0;
              b[j - 1]++; // Increment previous digit
            } else {
              k = j;
              break;
            }
          }
          c = b.Distinct().OrderBy(i => i).ToList(); // Update set of distinct digits
          var e = b.ToList();
          e.AddRange(d); // Combine old and new digits
          e = e.Distinct().OrderBy(i => i).ToList(); // Sort and get distinct again
          if (e.Distinct().Count() < p) { // If still missing digits
            int r = -1;
            for (int i = 0; i < e.Count(); i++) {
              if (e[i] == r + 1) {
                r = e[i];
              } else if (e[i] > 0 && d.Contains(e[i])) { // Found gap that was in original number
                o = e[i] - 1;
                r = e[i];
              }
              if (e[i] == q) // Reached the original last digit
                break;
              else if (e[i] >= q) { // If we've gone beyond original last digit
                o = p - 1;
              }
            }
            if (o < p - 1)
              o += (p - q); // Add to get final count
          } else
            o = p - q; // We have all digits, so compute simple difference
        } else {
          int r = -1;
          for (int i = 0; i < c.Count(); i++) {
            if (c[i] == r + 1) { // Consecutive sequence
              r = c[i];
            } else if (c[i] > 0) { // Gap in sequence
              o = c[i] - 1; // Count of operations needed to bridge this gap
              r = c[i];
            }
          }
          if (c.Last() < p - 1) // If we are still missing some higher digits
            o = p - 1;
          o -= b.Last(); // Subtract last digit to get correct count
        }
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/