// Problem: CF 2093 E - Min Max MEX
// https://codeforces.com/contest/2093/problem/E

/*
 * Problem: Min Max MEX
 * 
 * Algorithm: Binary search on the answer + greedy validation
 * 
 * Time Complexity: O(n * log(n)) per test case
 * Space Complexity: O(n) per test case
 * 
 * Approach:
 * - Binary search on the possible value of x (the minimum MEX).
 * - For each candidate x, check if it's possible to split the array into k subarrays, 
 *   such that each subarray has MEX >= x.
 * - To validate a candidate x:
 *   - Greedily scan the array.
 *   - Keep a boolean array to track which values from 0 to x-1 have been seen.
 *   - When we've seen all values from 0 to x-1, we increment the segment count and reset.
 *   - If at any point we have k or more segments, then it's feasible.
 * - This greedy approach works because we want to maximize the minimum MEX, so we try 
 *   to make as few segments as possible while still "covering" all values from 0 to x-1.
 * 
 * Input: Array of length n, number of segments k
 * Output: Maximum value of x such that all subarrays have MEX >= x
 */

using System;
using System.Linq;
public class Program {
  static bool Feasible(int x, int k, int[] a) {
    if (x == 0)
      return true; // If x is 0, MEX of any subarray is at least 0, so always possible
    int cnt = 0;
    bool[] seen = new bool[x]; // Track which values from 0 to x-1 are seen in current segment
    int need = x; // Number of values from 0 to x-1 still needed to be seen
    foreach (var num in a) {
      if (num < x && !seen[num]) { // Only consider values in valid range
        seen[num] = true;
        need--;
      }
      if (need == 0) { // All values from 0 to x-1 have been seen in current segment
        cnt++;
        if (cnt >= k) // If have enough segments, this x is feasible
          return true;
        need = x; // Reset for next segment
        Array.Clear(seen, 0, x); // Clear seen array for next segment
      }
    }
    return false; // Not enough segments to cover all required values
  }
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var nk = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int n = nk[0], k = nk[1];
      int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int lo = 0, hi = n + 1; // Binary search bounds: [0, n+1)
      while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (Feasible(mid, k, a))
          lo = mid + 1; // Try a larger x
        else
          hi = mid; // Try a smaller x
      }
      Console.WriteLine(lo - 1); // Final answer is one less than the last feasible value
    }
  }
}


// https://github.com/VaHiX/CodeForces/