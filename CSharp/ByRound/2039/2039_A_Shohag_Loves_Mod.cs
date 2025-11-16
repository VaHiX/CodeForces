// Problem: CF 2039 A - Shohag Loves Mod
// https://codeforces.com/contest/2039/problem/A

using System;
using System.Collections.Generic;

/*
 * Problem: Shohag Loves Mod
 * 
 * Purpose: 
 *   Given an integer n, construct an increasing sequence of n integers a_1 < a_2 < ... < a_n where each a_i is between 1 and 100.
 *   The condition is that for all pairs (i, j) with i < j, we must have a_i mod i != a_j mod j.
 *   
 * Algorithm:
 *   - For each index i from 1 to n, assign a_i = 2*i - 1.
 *   - This ensures a_i is always odd and strictly increasing.
 *   - Because a_i mod i = (2*i - 1) mod i = (2*i mod i - 1 mod i) = (0 - 1) mod i = (i - 1) mod i = i - 1.
 *   - Therefore, a_i mod i = i - 1 which means all remainders are distinct and different for each i.
 *   
 * Time Complexity: O(n) per test case
 *   - We iterate through the list once to assign values and once to output the result.
 * Space Complexity: O(n)
 *   - The space is used to store the sequence of n integers.
 */
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      long n = long.Parse(Console.ReadLine());
      List<long> sequence = new List<long>();
      for (long i = 1; i <= n; i++) {
        // Assign a_i = 2*i - 1 (odd numbers, increasing and within bounds)
        sequence.Add(2 * i - 1);
      }
      for (long i = 0; i < n; i++) {
        if (i > 0)
          Console.Write(" ");
        Console.Write(sequence[(int)i]);
      }
      Console.WriteLine();
    }
  }
}

// https://github.com/VaHiX/CodeForces/