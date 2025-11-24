// Problem: CF 1859 B - Olya and Game with Arrays
// https://codeforces.com/contest/1859/problem/B

/*
 * Problem: Olya and Game with Arrays
 * 
 * Purpose: 
 *   Maximize the beauty of a list of arrays, where beauty is the sum of minimum elements in each array.
 *   We can move at most one integer from each array to another array.
 * 
 * Algorithm:
 *   - For each array, find the minimum (min1) and second minimum (min2) elements.
 *   - Initially, sum up all the second minimums (min2) as the base answer.
 *   - To improve the result, we can move the smallest element from an array to another array.
 *   - The key insight is to find the best pair of arrays where moving one element can improve the sum:
 *     - Find the global minimum (min1Global) and global second minimum (min2Global).
 *     - Subtract (min2Global - min1Global) from the total to reflect the optimal move.
 * 
 * Time Complexity: O(sum of m_i) over all test cases
 * Space Complexity: O(1) - only using a few variables for tracking minima
 */

using System;
public class OlyaAndGameWithArrays {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      short n = short.Parse(Console.ReadLine());
      int min1Global = 1000000001; // Global minimum across all arrays
      int min2Global = 1000000001; // Global second minimum across all arrays
      long ans = 0; // Total beauty sum
      for (short j = 0; j < n; j++) {
        int mj = int.Parse(Console.ReadLine()); // Size of current array
        string[] parts = Console.ReadLine().Split(); // Elements of current array
        int min1 = 1000000001; // Minimum in current array
        int min2 = 1000000001; // Second minimum in current array
        for (int k = 0; k < mj; k++) {
          int ajk = int.Parse(parts[k]); // Current element
          if (ajk < min1) {
            min2 = min1; // Shift previous min to second min
            min1 = ajk;  // Update min
          } else if (ajk < min2)
            min2 = ajk; // Update second min if applicable
        }
        ans += min2; // Add second minimum to the total
        min1Global = Math.Min(min1Global, min1); // Update global minimum
        min2Global = Math.Min(min2Global, min2); // Update global second minimum
      }
      ans -= min2Global - min1Global; // Apply the optimal move
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/