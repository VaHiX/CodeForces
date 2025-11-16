// Problem: CF 1968 C - Assembly via Remainders
// https://codeforces.com/contest/1968/problem/C

using System;
public class AssemblyViaRemainders {
  /*
   * Problem: Given an array x_2, x_3, ..., x_n, find an array a_1, a_2, ..., a_n such that:
   *          x_i = a_i mod a_{i-1} for all i from 2 to n.
   *          All a_i must be in the range [1, 10^9].
   *
   * Algorithm:
   * - Start with a_1 = 501 (a value greater than any x_i, ensuring x_i < a_1 for all i > 1).
   * - For each subsequent element a_i, set a_i = a_{i-1} + x_i.
   *   This guarantees that a_i mod a_{i-1} = x_i because a_i > a_{i-1} and the difference is exactly x_i.
   *
   * Time Complexity: O(n) per test case, due to one loop over n elements.
   * Space Complexity: O(n) for storing the result array 'a'.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      short n = short.Parse(Console.ReadLine()); // Read size of array
      string[] parts = Console.ReadLine().Split(); // Read x values
      int[] a = new int[n]; // Initialize result array
      short m = Convert.ToInt16(n - 1); // Number of x values
      a[0] = 501; // Set first element to a value larger than max possible x_i (500)
      for (short j = 0; j < m; j++) {
        short xj = short.Parse(parts[j]); // Get current x value
        a[j + 1] = a[j] + xj; // Compute next element: a[i] = a[i-1] + x[i]
      }
      Console.WriteLine(string.Join(" ", a)); // Output the constructed array
    }
  }
}

// https://github.com/VaHiX/CodeForces/