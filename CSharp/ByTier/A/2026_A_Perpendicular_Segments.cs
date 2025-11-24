// Problem: CF 2026 A - Perpendicular Segments
// https://codeforces.com/contest/2026/problem/A

/*
 * Problem: Perpendicular Segments
 * 
 * Task: Given a coordinate plane and three integers X, Y, and K,
 *       find two line segments AB and CD such that:
 *       - Coordinates of A, B, C, D are integers within [0, X] and [0, Y]
 *       - Length of AB >= K and length of CD >= K
 *       - Segments AB and CD are perpendicular (lines containing them are perpendicular)
 * 
 * Approach:
 *   - For simplicity, we can place the first segment AB along the x-axis from (0, val) to (val, 0).
 *   - The second segment CD is placed from (0, 0) to (val, val).
 *   - This ensures both segments have length sqrt(2 * val^2) = val * sqrt(2), which is at least K if val >= K / sqrt(2).
 *   - This is optimized and works under given constraints.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
class Program {
  static void Main() {
    long t = Convert.ToInt64(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split(); // Read X, Y, K
      long a = Convert.ToInt64(input[0]);
      long b = Convert.ToInt64(input[1]);
      long k = Convert.ToInt64(input[2]);
      long val = Math.Min(a, b); // Choose smaller of X and Y to ensure constraints are met
      Console.WriteLine($"0 {val} {val} 0"); // Print first segment from (0, val) to (val, 0)
      Console.WriteLine($"0 0 {val} {val}"); // Print second segment from (0, 0) to (val, val)
    }
  }
}


// https://github.com/VaHiX/CodeForces/