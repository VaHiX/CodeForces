// Problem: CF 1901 A - Line Trip
// https://codeforces.com/contest/1901/problem/A

/*
 * Problem: Line Trip
 * 
 * Algorithm/Technique: Greedy approach with interval analysis
 * 
 * Time Complexity: O(n) per test case, where n is the number of gas stations.
 * Space Complexity: O(n) for storing the gas station positions.
 * 
 * The problem requires finding the minimum tank capacity to travel from 0 to x and back,
 * considering that refueling is only possible at gas stations.
 * 
 * Key insight:
 * - The tank capacity must be sufficient to cover the largest gap between consecutive gas stations.
 * - Additionally, we must ensure the return journey can be made, which includes the last segment
 *   from the final gas station back to 0.
 * 
 * Approach:
 * 1. Calculate the maximum gap between consecutive gas stations.
 * 2. Also consider the gap from the last gas station to the destination x.
 * 3. The required tank capacity is the maximum of all these gaps.
 */

using System;
class Program {
  static void Main() {
    long t = long.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] nk = Console.ReadLine().Split();
      long n = long.Parse(nk[0]);
      long k = long.Parse(nk[1]); // k represents x (destination)
      long[] a = new long[n + 1];
      a[0] = 0; // Start point is 0
      string[] aValues = Console.ReadLine().Split();
      for (long i = 1; i <= n; i++) {
        a[i] = long.Parse(aValues[i - 1]); // Fill gas station positions
      }
      long maximum = 0;
      bool flag = false;
      for (long i = 0; i < n; i++) {
        // Find maximum gap between adjacent gas stations
        maximum = Math.Max(maximum, a[i + 1] - a[i]);
        flag = true;
      }
      if (flag) {
        // Consider the journey from last gas station back to 0 (which is k - a[n])
        // We double it because we return to 0
        long maximum2 = (k - a[n]) * 2;
        maximum = Math.Max(maximum, maximum2);
      }
      Console.WriteLine(maximum);
    }
  }
}


// https://github.com/VaHiX/CodeForces/