// Problem: CF 2034 A - King Keykhosrow's Mystery
// https://codeforces.com/contest/2034/problem/A

/*
 * Problem: King Keykhosrow's Mystery
 * 
 * Purpose:
 *   This program finds the smallest positive integer m such that:
 *   1. m >= max(a, b)
 *   2. m % a == m % b
 *   
 *   The solution leverages the mathematical property that if m % a == m % b,
 *   then (m % a) = (m % b) = k for some k. This implies a divides (m - k)
 *   and b divides (m - k), so (m - k) is divisible by LCM(a, b).
 *   
 *   Therefore, the smallest such m is the LCM of a and b.
 *   
 * Algorithm:
 *   - Compute GCD of a and b using Euclidean algorithm
 *   - Compute LCM as (a * b) / GCD(a, b)
 *   
 * Time Complexity: O(log(min(a, b))) per test case due to GCD calculation
 * Space Complexity: O(1) - only using constant extra space
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) { // Process each test case
      string[] line = Console.ReadLine().Trim().Split(' '); // Read input line and split into parts
      var a = int.Parse(line[0]); // Parse first number
      var b = int.Parse(line[1]); // Parse second number
      getAns(a, b); // Compute and print result
    }
  }
  
  static void getAns(int a, int b) {
    var ans = a * b / gcd(a, b); // LCM(a,b) = (a * b) / GCD(a,b)
    Console.WriteLine(ans); // Output the answer
  }
  
  static int gcd(int a, int b) {
    if (a < b) // Ensure a >= b for simplification in recursion
      return gcd(b, a);
    while (b != 0) { // Euclidean algorithm implementation
      var w = a % b; // Store remainder
      a = b;         // Shift values
      b = w;
    }
    return a; // Return GCD
  }
}


// https://github.com/VaHiX/codeForces/