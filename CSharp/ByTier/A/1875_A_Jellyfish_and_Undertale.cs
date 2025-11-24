// Problem: CF 1875 A - Jellyfish and Undertale
// https://codeforces.com/contest/1875/problem/A

/*
 * Problem: Jellyfish and Undertale
 * 
 * Purpose:
 *   Given a bomb timer initialized to 'b', which decreases by 1 each second,
 *   and a set of tools that can be used at most once, each tool increases
 *   the timer by a value x_i. However, if applying a tool would make the
 *   timer exceed 'a', it is capped at 'a'. The goal is to maximize the
 *   total time until the bomb explodes by choosing the optimal sequence of tools.
 * 
 * Approach:
 *   Greedy strategy: For each tool, the maximum benefit we can get is
 *   min(x_i, a - 1), because after using the tool, we can at most go up to 'a'.
 *   We accumulate all such benefits to the initial timer value 'b'.
 * 
 * Time Complexity: O(n) per test case, where n is the number of tools.
 * Space Complexity: O(1) excluding input/output buffers.
 */

using System;
using System.Text;
public class JellyfishAndUndertale {
  public static void Main() {
    // Read number of test cases
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      // Parse the first line: a (max timer), b (initial timer), n (number of tools)
      string[] parts = Console.ReadLine().Split();
      int a = int.Parse(parts[0]);
      int b = int.Parse(parts[1]);
      byte n = byte.Parse(parts[2]);
      
      // Parse the second line: x_i values for each tool
      parts = Console.ReadLine().Split();
      long ansi = b; // Initialize result with the initial timer value
      
      // For each tool, add the maximum possible increase to the timer
      for (byte j = 0; j < n; j++) {
        int xj = int.Parse(parts[j]);
        ansi += Math.Min(xj, a - 1); // Greedily add max possible gain
      }
      
      ans.Append(ansi); // Append final result for current test case
      ans.AppendLine();
    }
    Console.Write(ans); // Output all results at once
  }
}


// https://github.com/VaHiX/CodeForces/