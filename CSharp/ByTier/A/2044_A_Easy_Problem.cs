// Problem: CF 2044 A - Easy Problem
// https://codeforces.com/contest/2044/problem/A

/* 
 * Problem: A. Easy Problem
 * Purpose: Calculate the number of ordered pairs of positive integers (a,b) such that a = n - b
 * Algorithms/Techniques: Mathematical observation and direct computation
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1) - only using constant extra space
 * 
 * For each n, we need to count positive integer pairs (a,b) where a = n - b.
 * Since both a and b must be positive integers, we have:
 * - b must be positive, so b ≥ 1
 * - a must be positive, so n - b ≥ 1, which means b ≤ n - 1
 * Therefore: 1 ≤ b ≤ n - 1
 * The number of valid values for b is (n - 1) - 1 + 1 = n - 1
 * But wait, let's reconsider: if b ranges from 1 to n-1, then a = n - b ranges from n-1 to 1.
 * So the count of pairs is simply n - 1.
 */

using System;
class _A_Easy_Problem {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read the value of n for current test case
      Console.WriteLine(n - 1); // Output the count of valid ordered pairs
    }
  }
}


// https://github.com/VaHiX/codeForces/