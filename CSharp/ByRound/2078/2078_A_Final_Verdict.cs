// Problem: CF 2078 A - Final Verdict
// https://codeforces.com/contest/2078/problem/A

﻿/*
 * Problem: Determine if an array of integers can be reduced to a single element equal to x
 *          by repeatedly splitting into k subsequences (where k divides the array length),
 *          calculating averages of each subsequence, and replacing the array with those averages.
 *
 * Algorithm: 
 *   - For each test case:
 *     - Parse input: n (length), x (target value)
 *     - Read array a of n integers
 *     - Calculate average of entire array
 *     - If average equals x, output "YES", otherwise "NO"
 *
 * Time Complexity: O(n) per test case (due to computing average of n elements)
 * Space Complexity: O(n) for storing the array
 */

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] nx = Console.ReadLine().Split(); // Read n and x
      int n = int.Parse(nx[0]); // Parse n
      int x = int.Parse(nx[1]); // Parse x
      int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray(); // Read array a
      double avg = a.Average(); // Compute average of the array
      if (avg == x) { // Check if average is equal to target value x
        Console.WriteLine("YES"); // If yes, output YES
      } else {
        Console.WriteLine("NO"); // Otherwise output NO
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/