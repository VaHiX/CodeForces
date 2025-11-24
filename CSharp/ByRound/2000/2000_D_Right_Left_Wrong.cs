// Problem: CF 2000 D - Right Left Wrong
// https://codeforces.com/contest/2000/problem/D

/*
 * Problem: D. Right Left Wrong
 * Purpose: Maximize score by pairing 'L' and 'R' segments such that the sum of elements between them is added to the score.
 * Algorithm:
 *   - Use prefix sums for efficient range sum queries.
 *   - Identify all 'L' and 'R' positions.
 *   - For each 'L', pair it with the closest suitable 'R' to its right (greedily).
 *   - Accumulate scores from valid ranges until no more operations are possible.
 *
 * Time Complexity: O(n) per test case, due to linear traversal of the array and operations on lists.
 * Space Complexity: O(n) for storing prefix sums and lists of L/R positions.
 */

using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      var s = Console.ReadLine().Trim();
      getAns(n, a, s);
    }
  }
  static void getAns(int n, long[] a, string s) {
    var b = new long[n]; // Prefix sum array
    b[0] = a[0];
    for (int i = 1; i < n; i++)
      b[i] = b[i - 1] + a[i]; // Build prefix sums
    
    var L = new List<int>(); // Store indices of 'L'
    var r = new List<int>(); // Store indices of 'R'
    for (int i = 0; i < n; i++) {
      if (s[i] == 'L')
        L.Add(i);
      else
        r.Add(i);
    }
    r.Reverse(); // Reverse to process R from right to left
    
    var Lc = L.Count;
    var rc = r.Count;
    var Lp = 0; // Pointer for L list
    var rp = 0; // Pointer for reversed R list
    var sum = 0L; // Total accumulated score
    
    while (Lp < Lc) {
      while (rp < rc) {
        if (r[rp] < L[Lp]) {
          // No valid R to the right of current L (this shouldn't happen in normal flow)
          Console.WriteLine(sum);
          return;
        }
        // Calculate sum between L[Lp] and r[rp] using prefix sums
        if (L[Lp] == 0)
          sum += b[r[rp]]; // If starting from index 0, no need to subtract earlier prefix
        else
          sum += b[r[rp]] - b[L[Lp] - 1];
        rp++; // Move to next R
        break; // Only take one valid pair per L
      }
      Lp++; // Move to next L
    }
    Console.WriteLine(sum);
  }
}


// https://github.com/VaHiX/codeForces/