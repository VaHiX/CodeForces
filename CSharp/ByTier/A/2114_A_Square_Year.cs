// Problem: CF 2114 A - Square Year
// https://codeforces.com/contest/2114/problem/A

/*
 * Problem: A. Square Year
 * 
 * Purpose:
 *   Given a 4-digit string representation of a year, determine if it can be expressed as (a + b)^2,
 *   where a and b are non-negative integers. If possible, output any valid pair (a, b).
 *   Otherwise, output -1.
 * 
 * Algorithm:
 *   - For each test case, parse the 4-digit string into an integer S.
 *   - Compute the square root of S and check if it's a perfect square.
 *   - If it is, then S = root^2, so we can write S as (0 + root)^2.
 *   - If not, return -1.
 * 
 * Time Complexity:
 *   O(t * 1) = O(t), where t is the number of test cases. Each operation inside the loop is constant time.
 * 
 * Space Complexity:
 *   O(1), only using a fixed amount of extra space regardless of input size.
 */

using System;
class Program {
  static void Main() {
    // Read and validate number of test cases
    if (!int.TryParse(Console.ReadLine(), out int t) || t < 1 || t > 10000) {
      Console.WriteLine("Invalid number of test cases.");
      return;
    }
    
    // Process each test case
    for (int i = 0; i < t; i++) {
      string s = Console.ReadLine();
      
      // Check if input is valid (4-digit string with digits only)
      if (s == null || s.Length != 4 || !int.TryParse(s, out int S) || S < 0 || S > 9999) {
        Console.WriteLine("-1");
        continue;
      }
      
      // Compute integer square root
      int root = (int)Math.Sqrt(S);
      
      // Check if S is a perfect square
      if (root * root == S) {
        Console.WriteLine($"0 {root}");
      } else {
        Console.WriteLine("-1");
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/