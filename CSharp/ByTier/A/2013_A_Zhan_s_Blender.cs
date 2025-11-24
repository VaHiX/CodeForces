// Problem: CF 2013 A - Zhan's Blender
// https://codeforces.com/contest/2013/problem/A

/*
 * Problem: A. Zhan's Blender
 * Purpose: Calculate minimum time to blend all fruits using a blender that can take 'y' fruits per second and blend 'x' fruits per second.
 * Algorithm: 
 *   - If n <= y, we can put all fruits in one go, so result = ceil(n / x)
 *   - If n > y, we calculate:
 *     1. Time to add all fruits: ceil(n / y) 
 *     2. Time to blend all fruits: ceil(n / x)
 *     3. Result is max of the two.
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      long n = long.Parse(Console.ReadLine()); // Read number of fruits
      string[] xy = Console.ReadLine().Split(); // Read x and y values
      long x = long.Parse(xy[0]); // Blender blending capacity per second
      long y = long.Parse(xy[1]); // Fruits Zhan can add per second
      
      if (n == 0) { // No fruits to blend
        Console.WriteLine(0);
        continue;
      }
      
      if (n <= y) { // We can add all fruits in one go
        long result = (n + x - 1) / x; // Ceiling division: (n + x - 1) / x
        Console.WriteLine(result);
      } else { // Need multiple steps to add and blend
        long secondsToAddFruits = (n + y - 1) / y;   // Time to add all fruits
        long secondsToBlendFruits = (n + x - 1) / x; // Time to blend all fruits
        long result = Math.Max(secondsToAddFruits, secondsToBlendFruits); // Take maximum of both
        Console.WriteLine(result);
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/