// Problem: CF 1977 B - Binary Colouring
// https://codeforces.com/contest/1977/problem/B

/*
 * Problem: Binary Colouring
 * 
 * Algorithm/Technique:
 * This problem asks to represent a given number x as a sum of powers of 2, 
 * where each coefficient is -1, 0, or 1. The representation must also satisfy 
 * a constraint: no two consecutive non-zero coefficients are allowed.
 * 
 * Approach:
 * 1. We use a greedy method to build the representation in base-2-like fashion.
 *    - If x is odd, we determine whether to add 1 or subtract 1 to make it even.
 *      This ensures we can represent x using a valid coefficient (-1, 0, 1).
 *    - We then divide x by 2 to move to the next power of 2.
 * 2. After generating the initial representation, we correct any consecutive non-zero
 *    entries by applying the constraint.
 * 
 * Time Complexity: O(log x), since we iterate through the bits of x.
 * Space Complexity: O(log x), for storing the coefficients.
 */

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int test = 0; test < t; test++) {
      long x = long.Parse(Console.ReadLine()); // Read the value x for current test case
      List<int> result = new List<int>(); // Store coefficients a_i
      while (x != 0) {
        if (x % 2 != 0) { // If x is odd
          if (x % 4 == 1) { // If x ≡ 1 (mod 4)
            result.Add(1); // Add 1 as coefficient
            x -= 1; // Subtract 1 to make x even
          } else { // If x ≡ 3 (mod 4)
            result.Add(-1); // Add -1 as coefficient
            x += 1; // Add 1 to make x even
          }
        } else {
          result.Add(0); // If x is even, coefficient is 0
        }
        x /= 2; // Move to next bit
      }
      // Correct consecutive non-zero coefficients
      for (int i = 0; i < result.Count - 1; i++) {
        if (result[i] != 0 && result[i + 1] != 0) {
          result[i] = 0; // Set current coefficient to 0
          result[i + 1] += (result[i + 1] == 1 ? 1 : -1); // Adjust next coefficient
        }
      }
      Console.WriteLine(result.Count); // Output length of array
      Console.WriteLine(string.Join(" ", result)); // Output the coefficients
    }
  }
}


// https://github.com/VaHiX/CodeForces/