// Problem: CF 2032 B - Medians
// https://codeforces.com/contest/2032/problem/B

using System;
public class Medians {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split(); // Parse n and k from input
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      
      // If k is the middle element of the array, we can make a single subarray
      if (k == (n + 1) / 2) {
        Console.WriteLine(1);
        Console.WriteLine(1);
      }
      // If k is even, we can split into 3 subarrays such that median of medians is k
      else if (k % 2 == 0 && k > 1 && k < n) {
        Console.WriteLine(3);
        Console.WriteLine("1 {0} {1}", k, k + 1);
      }
      // If k is odd, we can split into 3 subarrays such that median of medians is k
      else if (k % 2 > 0 && k > 2 && k < n - 1) {
        Console.WriteLine(3);
        Console.WriteLine("1 {0} {1}", k - 1, k + 2);
      }
      else
        Console.WriteLine(-1); // No valid partition exists
    }
  }
}
/*
 * Purpose: Solve the problem of partitioning an array [1..n] into m odd-length subarrays
 * such that the median of the medians equals k.
 *
 * Algorithms/Techniques:
 * - Greedy approach with special cases for even/odd k
 * - Direct construction based on properties of median and odd-length arrays
 *
 * Time Complexity: O(1) per test case, since all operations are constant time
 * Space Complexity: O(1), only using a fixed amount of variables regardless of input size
 */

// https://github.com/VaHiX/CodeForces/