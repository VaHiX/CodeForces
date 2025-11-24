// Problem: CF 2051 B - Journey
// https://codeforces.com/contest/2051/problem/B

/*
 * Problem: B. Journey
 * Purpose: Determine the day on which Monocarp completes his hiking journey,
 *          where he walks a, b, c kilometers on consecutive days in a repeating cycle.
 * 
 * Algorithm:
 * - Calculate total distance covered in one full cycle (a + b + c)
 * - Use integer division to find how many complete cycles are there
 * - Handle remainder to determine the partial day needed
 * - Use conditional checks for final day calculation based on accumulated distance
 * 
 * Time Complexity: O(1) - Constant time operations
 * Space Complexity: O(1) - Only constant extra space used
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var a = int.Parse(line[1]);
      var b = int.Parse(line[2]);
      var c = int.Parse(line[3]);
      getAns(n, a, b, c);
    }
  }
  static void getAns(int n, int a, int b, int c) {
    var t = a + b + c; // Total distance in one cycle of 3 days
    var w = n / t;     // Number of complete cycles
    var r = n % t;     // Remaining distance after complete cycles
    
    if (r == 0) {
      Console.WriteLine(w * 3); // If exactly divisible, last day is end of a cycle
      return;
    }
    
    var s = w * t;     // Distance covered in full cycles
    s += a;            // Add first day of next cycle
    
    if (s >= n) {
      Console.WriteLine(w * 3 + 1); // First day of new cycle is sufficient
      return;
    }
    
    s += b;            // Add second day of next cycle
    
    if (s >= n) {
      Console.WriteLine(w * 3 + 2); // Second day of new cycle is sufficient
      return;
    }
    
    Console.WriteLine(w * 3 + 3); // Third day of new cycle is needed
  }
}


// https://github.com/VaHiX/codeForces/