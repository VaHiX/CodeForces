// Problem: CF 1928 A - Rectangle Cutting
// https://codeforces.com/contest/1928/problem/A

/*
 * Problem: Rectangle Cutting
 * 
 * Purpose: Determine if a rectangle of size a×b can be cut into two integer-sided rectangles,
 *          and then rearranged to form a different rectangle (considering rotations as the same).
 * 
 * Algorithms/Techniques:
 * - Mathematical analysis of possible cuts and resulting configurations
 * - Check divisibility and equality conditions to determine if reconfiguration is possible
 * 
 * Time Complexity: O(1) - Constant time per test case, as all operations are basic arithmetic checks.
 * Space Complexity: O(1) - Only a fixed amount of variables are used, regardless of input size.
 */

using System;

public class RectangleCutting {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split(); // Split input line into two parts
      int a = int.Parse(parts[0]); // First dimension of the rectangle
      int b = int.Parse(parts[1]); // Second dimension of the rectangle
      
      // The logic checks three conditions:
      // 1. Both dimensions are even -> can cut into two rectangles with integer sides
      // 2. a is even but a/2 != b -> can form a new rectangle
      // 3. b is even but b/2 != a -> can form a new rectangle
      bool ans = ((a % 2 == 0 && b % 2 == 0) || (a % 2 == 0 && a / 2 != b) ||
                  (b % 2 == 0 && b / 2 != a));
      
      Console.WriteLine(ans ? "Yes" : "No"); // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/