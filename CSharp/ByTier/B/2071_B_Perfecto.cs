// Problem: CF 2071 B - Perfecto
// https://codeforces.com/contest/2071/problem/B

/*
 * Problem: B. Perfecto
 * 
 * Purpose: Given a positive integer n, find a permutation of length n such that the prefix sums are not perfect squares.
 *          If no such permutation exists, return -1.
 * 
 * Algorithm:
 *   - For most values of n, construct a valid permutation by swapping elements at specific indices.
 *   - Special cases where n is one of the predefined values in 'aa' result in -1 (as they are known to have no solution).
 *   - The method uses a range-based approach to build permutation and then performs swaps for certain indices.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

using System.Linq;
using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      getAns(n);
    }
  }
  static void getAns(int n) {
    // List of problematic values for which no solution exists
    var aa = new List<int>() { 1, 8, 49, 288, 1681, 9800, 57121, 332928 };
    if (aa.Contains(n)) {
      Console.WriteLine(-1);
      return;
    }
    // Create initial permutation [1, 2, ..., n]
    var ans = Enumerable.Range(1, n).ToArray();
    // For each value in 'aa', perform a swap to avoid perfect square prefix sums
    for (int i = 0; i < 8; i++) {
      if (n > aa[i]) {
        var w = ans[aa[i] - 1];          // Store element at position aa[i]-1
        ans[aa[i] - 1] = ans[aa[i]];     // Swap with next element
        ans[aa[i]] = w;                  // Complete the swap
      }
    }
    Console.WriteLine(string.Join(" ", ans));
  }
}


// https://github.com/VaHiX/codeForces/