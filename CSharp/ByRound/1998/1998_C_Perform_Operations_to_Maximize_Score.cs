// Problem: CF 1998 C - Perform Operations to Maximize Score
// https://codeforces.com/contest/1998/problem/C

/*
 * Problem: Perform Operations to Maximize Score
 * 
 * Approach:
 * - We use binary search on the answer to find the maximum possible score.
 * - For a given score value 'mid', we check if it's achievable by:
 *   1. Trying to make one element (where b[i] == 1) large enough so that a[i] + median(c[i]) >= mid.
 *   2. For other elements (where b[i] == 0), determine if we can boost them to reach the required median.
 * - Sorting indices in descending order of a[i] to prioritize larger elements for optimization.
 * - Time complexity: O(n log(10^12) * n) which simplifies to O(n^2 * log(10^12)) in worst case.
 * - Space complexity: O(n) for storing sorted indices and auxiliary arrays.
 */

using System;
using System.Linq;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var input = Console.ReadLine().Split();
      int n = int.Parse(input[0]);
      int k = int.Parse(input[1]);
      var a = Console.ReadLine().Split().Select(long.Parse).ToArray();
      var b = Console.ReadLine().Split().Select(int.Parse).ToArray();
      var ord = Enumerable.Range(0, n).ToArray();
      // Sort indices based on a[i] in descending order
      Array.Sort(ord, (i, j) => a[j].CompareTo(a[i]));
      int need = ((n - 1) >> 1) + 1; // Number of elements needed for median
      long low = 0, high = 1_000_000_000_0L; // Binary search bounds
      while (low < high) {
        long mid = (low + high + 1) >> 1; // Midpoint for binary search
        bool ok = false;
        // Try to see if we can set an element (b[i] == 1) to at least (mid - a[i]) to get score >= mid
        for (int i = 0; i < n; i++) {
          int idx = ord[i];
          if (b[idx] == 1) {
            if (a[idx] + k >= mid) {
              ok = true;
            } else {
              long x = mid - a[idx] - k; // Required value after applying ops
              int rem = need;
              for (int j = 0; j < n; j++) {
                int jdx = ord[j];
                if (jdx == idx) {
                  continue;
                }
                if (rem == 0) {
                  break;
                }
                if (a[jdx] >= x)
                  rem--;
              }
              if (rem == 0)
                ok = true;
            }
            break;
          }
        }
        // Check if any element (b[i] == 0) can be used for achieving the score
        for (int i = 0; i < n; i++) {
          int idx = ord[i];
          if (b[idx] == 0) {
            int rem = need;
            long sum = 0;
            long x = mid - a[idx];
            for (int j = 0; j < n; j++) {
              int jdx = ord[j];
              if (jdx == idx) {
                continue;
              }
              if (rem == 0) {
                break;
              }
              if (a[jdx] >= x)
                rem--;
              else if (b[jdx] == 1) {
                sum += x - a[jdx];
                rem--;
              }
            }
            if (rem == 0 && sum <= k)
              ok = true;
            break;
          }
        }
        // Adjust binary search boundaries based on feasibility
        low = ok ? mid : low;
        high = !ok ? mid - 1 : high;
      }
      Console.WriteLine(low);
    }
  }
}


// https://github.com/VaHiX/CodeForces/