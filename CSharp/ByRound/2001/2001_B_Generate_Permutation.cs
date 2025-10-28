// Problem: CF 2001 B - Generate Permutation
// https://codeforces.com/contest/2001/problem/B

using System;
public class GeneratePermutation {
  /*
   * Purpose: Generate a permutation of [1, 2, ..., n] such that the minimum number of carriage return operations
   *          needed to construct the array using either typewriter (left-to-right or right-to-left) is the same.
   * 
   * Algorithm: 
   *   - If n is even, it's impossible to balance the carriage returns, so return -1.
   *   - If n is odd, construct a specific symmetric permutation centered around the middle element.
   *     The idea is to arrange the numbers in a way that minimizes the difference in operations 
   *     between the two typewriters, by placing large numbers toward the centers of both directions.
   * 
   * Time Complexity: O(n) - Single loop to generate the permutation.
   * Space Complexity: O(n) - For storing the permutation array.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      if (n % 2 == 0)
        Console.WriteLine(-1);
      else {
        int[] p = new int[n];
        int idxCenter = n / 2; // Find the center index
        for (int j = 0; j < n; j++) {
          int d = j - idxCenter; // Calculate distance from center
          p[j] = d < 0 ? 2 * (-d) + 1 : d > 0 ? 2 * d : 1; // Assign values based on distance
        }
        Console.WriteLine(string.Join(" ", p));
      }
    }
  }
}

// https://github.com/VaHiX/CodeForces/