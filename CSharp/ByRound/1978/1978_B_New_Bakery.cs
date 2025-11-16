// Problem: CF 1978 B - New Bakery
// https://codeforces.com/contest/1978/problem/B

using System;
public class NewBakery {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int a = int.Parse(parts[1]);
      int b = int.Parse(parts[2]);
      long ans = 0;
      // If the modified price b is less than or equal to the usual price a,
      // selling all buns at price a yields maximum profit
      if (b <= a)
        ans = (long)n * a;
      else {
        // Determine optimal number of buns to sell at modified price
        int k = Math.Min(n, b - a);
        // Calculate sum of modified prices using arithmetic series formula:
        // Sum = k * (first + last) / 2 = k * (2*b - k + 1) / 2
        ans = ((long)k * (2 * b - k + 1)) / 2;
        // Add profit from remaining buns sold at usual price a
        ans += (long)a * (n - k);
      }
      Console.WriteLine(ans);
    }
  }
}
/*
 * Algorithm: Greedy with arithmetic series
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Techniques:
 * - Arithmetic series sum formula for efficient calculation
 * - Conditional logic to choose optimal k value
 * - Use of long to prevent integer overflow
 */

// https://github.com/VaHiX/CodeForces/