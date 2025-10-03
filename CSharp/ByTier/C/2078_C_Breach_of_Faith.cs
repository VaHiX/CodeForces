// Problem: CF 2078 C - Breach of Faith
// https://codeforces.com/contest/2078/problem/C

/*
 * Problem: C. Breach of Faith
 * Purpose: Recover a hidden sequence 'a' from a shuffled and one-element-deleted sequence 'b'
 * Algorithm:
 *   - Sort the given sequence b.
 *   - Place elements in alternating positions to satisfy the condition:
 *     a[1] = a[2] - a[3] + a[4] - a[5] + ... + a[2n] - a[2n+1]
 *   - Use sum difference technique to find the missing element.
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for the auxiliary arrays
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      List<long> b = Console.ReadLine().Split().Select(long.Parse).ToList();
      b.Sort(); // Sort the input to help reconstruct the sequence
      long[] a = new long[2 * n + 1];
      // Fill even indices with larger elements from sorted list
      for (int i = 0; i <= n; i++) {
        a[2 * i] = b[n + i - 1];
      }
      // Fill odd indices with smaller elements
      for (int i = 0; i < n - 1; i++) {
        a[2 * i + 1] = b[i];
      }
      // Compute the sum of larger elements and smaller ones to deduce missing element
      long sumLarge = b.Skip(n - 1).Sum();
      long sumSmall = b.Take(n - 1).Sum();
      a[2 * n - 1] = sumLarge - sumSmall;
      Console.WriteLine(string.Join(" ", a));
    }
  }
}


// https://github.com/VaHiX/codeForces/