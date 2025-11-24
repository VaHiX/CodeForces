// Problem: CF 2091 D - Place of the Olympiad
// https://codeforces.com/contest/2091/problem/D

/*
 * Problem: D. Place of the Olympiad
 * 
 * Purpose: Given a venue with n rows and m columns of desks, and k participants,
 *          assign desks such that the maximum bench length (consecutive desks)
 *          is minimized.
 * 
 * Algorithm: Binary Search on Answer
 * 
 * Time Complexity: O(log(min(n, m)) * t), where t is number of test cases.
 * Space Complexity: O(1)
 * 
 * Techniques:
 * - Binary search over the possible maximum bench length.
 * - For each candidate length, check if it's feasible to place all k desks
 *   such that no bench exceeds this length.
 * 
 * Approach:
 * - Use binary search on the answer to find the minimum possible longest bench.
 * - For a given bench length 'mid', compute how many desks can be placed
 *   without exceeding 'mid' as the maximum bench length.
 * - The key observation is that placing desks optimally means filling rows
 *   with at most 'mid' desks in any consecutive sequence and spreading them evenly.
 */

using System;
using System.Text;
class Program {
  static void Main(string[] args) {
    int q = int.Parse(Console.ReadLine());
    while (q-- > 0) {
      Task_D.Solve();
    }
  }
  public static class Task_D {
    public static void Solve() {
      var args = Console.ReadLine().Split();
      long n = long.Parse(args[0]);
      long m = long.Parse(args[1]);
      long k = long.Parse(args[2]);
      long mid;
      long l = 0, r = m; // Binary search range: from 0 to m (maximum possible bench length)
      while (l + 1 < r) {
        mid = (l + r) / 2;
        // Check if it's possible to place k desks without any bench exceeding 'mid'
        // In each row, we can fit at most `m/(mid+1)` full benches of length `mid`
        // and possibly one partial group with remaining spots.
        if ((n * (mid * (m / (mid + 1)) + m % (mid + 1))) >= k) {
          r = mid; // Try smaller maximum bench length
        } else {
          l = mid; // Need to increase the max bench length
        }
      }
      Console.WriteLine(r);
    }
  }
}


// https://github.com/VaHiX/codeForces/