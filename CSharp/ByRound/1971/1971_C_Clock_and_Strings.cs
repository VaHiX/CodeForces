// Problem: CF 1971 C - Clock and Strings
// https://codeforces.com/contest/1971/problem/C

using System;
public class ClockAndStrings {
  /*
   * Purpose: Determine if two strings connecting pairs of points on a clock intersect.
   * 
   * Algorithm:
   * - Normalize the endpoints of the first string (a, b) so that a <= b.
   * - Check if the second string (c, d) crosses the first string by:
   *   - If c lies between a and b, then d must lie outside the range [a, b].
   *   - If d lies between a and b, then c must lie outside the range [a, b].
   * - The intersection occurs if either of these conditions is true.
   * 
   * Time Complexity: O(1) - Constant time per test case.
   * Space Complexity: O(1) - Constant space used.
   */
  
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte a = byte.Parse(parts[0]);
      byte b = byte.Parse(parts[1]);
      byte c = byte.Parse(parts[2]);
      byte d = byte.Parse(parts[3]);
      
      // Normalize the first string so that a <= b
      if (a > b) {
        byte tmp = a;
        a = b;
        b = tmp;
      }
      
      // Check if c is inside [a,b] and d is outside, or vice versa
      bool c1 = (c >= a && c <= b && (d < a || d > b));
      bool c2 = (d >= a && d <= b && (c < a || c > b));
      
      // If either condition is satisfied, the strings intersect
      bool ans = (c1 || c2);
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/