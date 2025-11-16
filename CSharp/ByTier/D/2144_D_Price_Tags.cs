// Problem: CF 2144 D - Price Tags
// https://codeforces.com/contest/2144/problem/D

/*
 * Problem: D. Price Tags
 * 
 * Purpose: Maximize total income by choosing an optimal coefficient x for price reduction,
 *          where new price is ceil(c_i / x). Income = sum of new prices - cost of printing
 *          new price tags.
 * 
 * Algorithm: 
 *   - For each candidate x from 2 to max_price + 1:
 *     - Calculate new prices using ceiling division
 *     - Count how many items exist at each new price
 *     - Compute income = sum of new prices - cost of printing new tags
 *   - Use prefix sums to efficiently compute counts of items in ranges
 * 
 * Time Complexity: O(max(c) * max(c)), where max(c) is the maximum price.
 * Space Complexity: O(max(c)), for frequency and prefix arrays.
 */
using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split();
      int n = int.Parse(input[0]);
      long y = long.Parse(input[1]);
      int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      int m = a.Max();
      int[] f = new int[m + 1]; // Frequency array to count occurrences of each price
      foreach (int v in a) {
        if (v <= m)
          f[v]++;
      }
      int[] p = new int[m + 1]; // Prefix sum array for efficient range queries
      for (int i = 1; i <= m; i++)
        p[i] = p[i - 1] + f[i];
      long b = long.MinValue; // Maximum income found so far
      for (int x = 2; x <= m + 1; x++) {
        int mk = (m + x - 1) / x; // Number of distinct new prices
        long s = 0; // Sum of new prices
        long r = 0; // Number of existing tags that can be reused
        for (int k = 1; k <= mk; k++) {
          int L = (k - 1) * x + 1; // Left bound of current range
          int R = Math.Min(k * x, m); // Right bound of current range
          if (L > R)
            continue;
          int z = p[R] - p[L - 1]; // Count of items in range [L, R]
          if (z == 0)
            continue;
          s += (long)k * z; // Accumulate value of new prices
          if (k <= m)
            r += Math.Min(z, f[k]); // How many old tags of price k can be reused
        }
        long pr = n - r; // Number of new tags to print
        long inc = s - y * pr; // Total income for this x
        if (inc > b)
          b = inc;
      }
      Console.WriteLine(b);
    }
  }
}


// https://github.com/VaHiX/CodeForces/