// Problem: CF 1883 C - Raspberries
// https://codeforces.com/contest/1883/problem/C

/*
 * Problem: C. Raspberries
 * Algorithm: Greedy approach to find minimum operations to make product divisible by k
 * Time Complexity: O(n) per test case, where n is the size of array
 * Space Complexity: O(1) - only using a few variables regardless of input size
 * 
 * Approach:
 * - For each element in array, compute remainder when divided by k
 * - Compute the product of all remainders modulo k
 * - If product is not 0 (i.e., not already divisible by k), calculate minimum operations:
 *   - If k=4, handle special cases based on the product and max remainder
 *   - Otherwise, use the formula k - max remainder
 */

using System;
public class Raspberries {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      byte k = byte.Parse(parts[1]);
      parts = Console.ReadLine().Split();
      byte rp = 1; // cumulative product of remainders
      byte rMax = 0; // maximum remainder encountered
      for (int j = 0; j < n; j++) {
        byte aj = byte.Parse(parts[j]);
        byte r = Convert.ToByte(aj % k); // compute remainder of current element
        rp = Convert.ToByte((rp * r) % k); // multiply and take modulo k
        rMax = Math.Max(rMax, r); // track maximum remainder
      }
      byte ans = 0;
      // Special case for k=4
      if (k == 4 && rp > 0) {
        // If the product is 2 (mod 4), we need 1 operation to make it 0 (mod 4)
        // If max remainder is 3, we need 1 operation
        // Otherwise, we need 2 operations
        ans = Convert.ToByte(rp == 2 ? 1 : (rMax == 3 ? 1 : 2));
      } else if (rp > 0) {
        // For other values of k, answer is k - rMax
        ans = Convert.ToByte(k - rMax);
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/