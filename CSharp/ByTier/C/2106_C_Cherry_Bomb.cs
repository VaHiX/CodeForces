// Problem: CF 2106 C - Cherry Bomb
// https://codeforces.com/contest/2106/problem/C

/*
 * Problem: C. Cherry Bomb
 * 
 * Purpose: Count the number of possible arrays b such that a and b are complementary,
 *          i.e., there exists an integer x such that a[i] + b[i] = x for all i.
 *          Missing elements in b (denoted by -1) must be replaced with non-negative integers
 *          not greater than k.
 * 
 * Algorithm:
 * 1. For each test case, determine the constant sum x that makes a and b complementary.
 * 2. Iterate through arrays a and b to identify constraints on x from fixed elements.
 * 3. Based on constraints and range [0, k], compute how many valid values of x exist,
 *    which directly gives the number of ways to fill in missing b values.
 * 
 * Time Complexity: O(n) per test case, since we process each element once.
 * Space Complexity: O(1), ignoring input storage.
 */

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace ConsoleApp1 {
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int y = 0; y < t; y++) {
      string[] s0 = Console.ReadLine().Split(' ');
      int n = int.Parse(s0[0]);
      int k = int.Parse(s0[1]);
      string[] s1 = Console.ReadLine().Split(' ');
      string[] s2 = Console.ReadLine().Split(' ');
      int c = -1, min = -1, max = -1, ans = -1;
      
      // Loop through all elements to determine constraints
      for (int i = 0; i < s1.Length; i++) {
        int a = int.Parse(s1[i]), b = int.Parse(s2[i]);
        
        // Track maximum and minimum values of 'a' to derive range of valid sums
        if (a > max || max == -1) {
          max = a;
        }
        if (a < min || min == -1) {
          min = a;
        }
        
        // If current element in b is known, check compatibility with previous known elements
        if (b != -1) {
          if (c == -1) {
            c = b + a;  // Determine expected sum x = a[i] + b[i]
          } else if (a + b != c) {
            ans = 0;  // Incompatible values: impossible to make complementary arrays
          }
        }
      }
      
      // Check whether constraints are consistent or contradictory
      if (ans == 0 || min + k < max) {
        Console.WriteLine($"0");  // Impossible due to contradiction or range overflow
      } else if (c != -1) {
        // When sum x is already determined, check whether it fits within bounds
        if (c - max < 0 || c - min > k) {
          Console.WriteLine($"0");  // No valid x satisfies all constraints
        } else {
          Console.WriteLine($"1");  // Only one way to fill in the array
        }
      } else {
        // Sum x is not determined yet; calculate number of possible values for x
        // Range of valid x values is [min + 0, max + k]
        // So number of valid x's = (max + k) - (min + 0) + 1 = k + max - min + 1.
        Console.WriteLine($"{1 + k - (max - min)}");
      }
    }
  }
}
}


// https://github.com/VaHiX/codeForces/