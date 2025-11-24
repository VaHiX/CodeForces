// Problem: CF 2020 A - Find Minimum Operations
// https://codeforces.com/contest/2020/problem/A

﻿/*
 * Code Purpose: This program calculates the minimum number of operations required to reduce a given integer n to 0,
 * by subtracting powers of k in each operation. The approach uses the base-k representation of n to count the digits,
 * which corresponds to the number of operations needed.
 *
 * Algorithm/Techniques:
 * - Greedy approach using base-k number system
 * - For each digit in base-k representation of n, we add that digit to the total operations
 * 
 * Time Complexity: O(log_k(n)) per test case, since we process each digit of n in base k.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split(); // Read n and k from input
      long n = long.Parse(input[0]); // Parse n
      long k = long.Parse(input[1]); // Parse k
      long operations = 0; // Initialize operation counter
      
      if (k == 1) {
        // Special case: if k is 1, we must subtract 1 repeatedly
        operations = n;
      } else {
        // General case: compute sum of digits in base-k representation of n
        while (n > 0) {
          operations += (n % k); // Add the last digit in base-k
          n /= k; // Move to next digit
        }
      }
      Console.WriteLine(operations); // Output result
    }
  }
}


// https://github.com/VaHiX/codeForces/