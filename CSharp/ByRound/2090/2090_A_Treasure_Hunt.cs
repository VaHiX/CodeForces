// Problem: CF 2090 A - Treasure Hunt
// https://codeforces.com/contest/2090/problem/A

/*
 * Problem: Treasure Hunt
 * 
 * Purpose: Determine who digs up the treasure first based on alternating turns.
 *          Little B starts digging on day 1, then Little K on day 2, and so on.
 *          Each person digs a fixed depth per day (x for B, y for K).
 *          The treasure is buried at a depth of 'a.5' meters.
 * 
 * Algorithm: 
 *   - Simulate the digging process day by day.
 *   - Keep track of total depth dug so far.
 *   - On each odd-numbered turn (i.e., B's turn), add x meters; on even turns (K's), add y.
 *   - If at any point the total depth exceeds a.5, check whose turn it was.
 *   - Return "NO" if B dug it up first, otherwise return "YES".
 * 
 * Time Complexity: O(1) per test case since we do a maximum of 2 iterations (since x,y,a <= 10^9,
 *                   the depth exceeds 'a.5' within at most 2 turns, or in one if both x and y are large).
 * Space Complexity: O(1) - only using constant extra space.
 */

using System;
public class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] s = Console.ReadLine().Split(); // Split input line into parts
      int x = int.Parse(s[0]); // Depth dug by B per day
      int y = int.Parse(s[1]); // Depth dug by K per day
      int a = int.Parse(s[2]); // Total depth of treasure (in meters)
      
      // Check if treasure is dug up during B's turn (odd day) or K's turn (even day)
      // If the cumulative depth after the current step is less than x, then it was B's turn
      // Otherwise, it was K's turn.
      Console.WriteLine(((a % (x + y)) < x) ? "NO" : "YES");
    }
  }
}


// https://github.com/VaHiX/codeForces/