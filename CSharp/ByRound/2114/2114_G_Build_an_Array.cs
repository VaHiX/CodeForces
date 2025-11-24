// Problem: CF 2114 G - Build an Array
// https://codeforces.com/contest/2114/problem/G

/*
 * Problem: G. Build an Array
 * Purpose: Determine if a given array can be obtained by performing exactly k operations on an empty array,
 *          where each operation adds an integer to either end, and adjacent duplicates are summed.
 * Algorithm:
 *   - Preprocess suffix sums using Cal() and Cc() functions to calculate contribution of elements.
 *   - Use prefix and suffix processing to simulate all possible ways of building the array with k operations.
 *   - Check if maximum possible score (sum of contributions) is at least k.
 *
 * Time Complexity: O(n) per test case, where n is the length of array a.
 * Space Complexity: O(n), for storing arrays suf and a.
 */

using System;
using System.Collections.Generic;
class Program {
  static int Cal(int a, int b) {
    int c = 0, d = 0;
    // Count how many times 'b' is divisible by 2
    while (b % 2 == 0) {
      b /= 2;
      c++;
    }
    // Count how many times 'a' is divisible by 2
    while (a % 2 == 0) {
      a /= 2;
      d++;
    }
    // Return calculated value based on bit shifts and comparison
    return (1 << c) - ((a == b && d < c) ? (1 << (d + 1)) - 1 : 0);
  }
  static int Cc(int x) {
    int c = 0;
    // Count how many times 'x' is divisible by 2 using bit shifting
    while (x % 2 == 0) {
      x >>= 1;
      c++;
    }
    // Return power of 2 based on count
    return 1 << c;
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    const string Y = "yes";
    const string N = "no";
    while (t-- > 0) {
      var inputs = Console.ReadLine().Split();
      int n = int.Parse(inputs[0]);
      int k = int.Parse(inputs[1]);
      var a = new int[n];
      var suf = new long[n]; // Suffix array for precomputed values
      var aInputs = Console.ReadLine().Split();
      for (int i = 0; i < n; i++) {
        a[i] = int.Parse(aInputs[i]);
      }
      // Compute suffix sum from right to left
      suf[n - 1] = 0;
      for (int i = n - 2; i >= 0; i--) {
        suf[i] = suf[i + 1] + Cal(a[i], a[i + 1]);
      }
      long mx = 0, pr = 0; // 'mx' tracks max score, 'pr' tracks prefix sum
      for (int i = 0; i < n; i++) {
        // Calculate current maximum possible value considering prefix and suffix
        mx = Math.Max(mx, suf[i] + pr + Cc(a[i]));
        if (i < n - 1)
          pr += Cal(a[i + 1], a[i]); // Update prefix sum
      }
      // Output result based on whether maximum score meets required k
      Console.WriteLine(mx >= k ? Y : N);
    }
  }
}


// https://github.com/VaHiX/codeForces/