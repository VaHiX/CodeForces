// Problem: CF 2028 C - Alice's Adventures in Cutting Cake
// https://codeforces.com/contest/2028/problem/C

/*
 * Problem: Alice's Adventures in Cutting Cake
 * 
 * Purpose:
 *   - Given a cake with n sections having tastiness values, and m creatures
 *     each requiring at least v tastiness, partition the cake into m+1 pieces
 *     such that each creature gets a piece of at least v tastiness.
 *   - Maximize the tastiness of Alice's own piece under the constraint.
 * 
 * Algorithm:
 *   - Use prefix sums to quickly compute sums of subarrays.
 *   - Precompute "forward" and "backward" segments where we can assign
 *     valid pieces to creatures from both ends.
 *   - Use two pointers from left and right to find valid segments satisfying v.
 *   - For each valid combination of left and right segments, calculate the
 *     remaining sum for Alice and track the maximum.
 * 
 * Time Complexity:
 *   - O(n * m) in worst case due to segment processing, but optimized through
 *     two-pointer techniques and prefix sums.
 *   - Actual effective complexity per test case: O(n)
 * 
 * Space Complexity:
 *   - O(n) for storing prefix sums and segment arrays.
 * 
 * Techniques Used:
 *   - Prefix Sum Technique
 *   - Two Pointer Technique
 *   - Greedy Segment Assignment
 */

using System;
using System.Linq;
class Solution {
  static void Solve() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var nmv = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long n = nmv[0], m = nmv[1], v = nmv[2];
      long[] a = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long[] p = new long[n + 1];
      Array.Copy(a, p, n);
      for (int i = 1; i <= n; i++)
        p[i] += p[i - 1]; // Compute prefix sums
      
      long[] sf = new long[m + 1]; // sf[k]: sum of first k valid segments from left
      long[] le = new long[m + 1]; // le[k]: ending index of k-th segment from left
      sf[0] = 0;
      le[0] = -1;
      long l = 0;
      for (int k = 1; k <= m; k++) {
        sf[k] = (l >= n) ? long.MaxValue : sf[k];
        le[k] = (l >= n) ? n : le[k];
        if (l >= n)
          continue;
        long r = l, sum = 0;
        for (; r < n && sum < v; r++) { // Find next segment of at least v
          sum += a[r];
        }
        bool isValid = sum >= v;
        sf[k] = isValid ? sf[k - 1] + sum : long.MaxValue;
        le[k] = isValid ? r - 1 : n;
        l = isValid ? r : l;
      }
      
      long[] se = new long[m + 1]; // se[k]: sum of first k valid segments from right
      long[] fs = new long[m + 1]; // fs[k]: starting index of k-th segment from right
      se[0] = 0;
      fs[0] = n;
      long rPtr = n - 1;
      for (int k = 1; k <= m; k++) {
        bool shouldContinue = rPtr < 0;
        se[k] = shouldContinue ? long.MaxValue : se[k];
        fs[k] = shouldContinue ? -1 : fs[k];
        if (shouldContinue)
          continue;
        long lPtr = rPtr, sum = 0;
        do {
          sum += a[lPtr--]; // Traverse backwards to find valid segment
        } while (lPtr >= 0 && sum < v);
        se[k] = (sum >= v) ? se[k - 1] + sum : long.MaxValue;
        fs[k] = (sum >= v) ? lPtr + 1 : -1;
        if (sum >= v) {
          rPtr = lPtr; // Move pointer to start of valid segment
        }
      }
      
      long S = p[n], ma = -1;
      for (int k = 0; k <= m; k++) {
        // Ensure there's overlap or no overlap needed in both directions
        if (Math.Min(sf[k], se[m - k]) < long.MaxValue &&
            (k == 0 ? true : (m - k == 0 ? true : le[k] < fs[m - k]))) {
          long sumAssigned = sf[k] + se[m - k];
          ma = Math.Max(ma, S - sumAssigned);
        }
      }
      Console.WriteLine(ma >= 0 ? ma.ToString() : "-1");
    }
  }
  static void Main() { Solve(); }
}


// https://github.com/VaHiX/CodeForces/