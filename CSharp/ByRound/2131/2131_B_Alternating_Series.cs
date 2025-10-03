// Problem: CF 2131 B - Alternating Series
// https://codeforces.com/contest/2131/problem/B

/*
 * Problem: B. Alternating Series
 * Purpose: Generate a "good" array of length n that satisfies two conditions:
 *   1. Adjacent elements have negative product (alternating signs)
 *   2. All subarrays of length >= 2 have positive sums
 * Additionally, among all good arrays of same length, output the lexicographically smallest one
 * when considering absolute values.
 * 
 * Algorithm/Techniques:
 *   - Greedy approach: Build an alternating array starting with -1, then 3, -1, 3, ...
 *     For even indices (after first), we use 3 to keep sum positive.
 *   - Special handling for last element in odd-length arrays.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for output string builder
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1 {
class Program {
  static long GCD(long x, long y) {
    while (y != 0) {
      long temp = y;
      y = x % y;
      x = temp;
    }
    return x;
  }
  
  static void Main(string[] args) {
    int t = Convert.ToInt16(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = Convert.ToInt32(Console.ReadLine()); // Read length of array
      string ans = "";
      var sb = new System.Text.StringBuilder(); // Use StringBuilder for efficient string building
      
      for (int i = 1; i <= n; i++) {
        if (i % 2 != 0) {
          // For odd positions, append -1 to alternate signs
          sb.Append("-1");
        } else if (i == n) {
          // Last element in even-length arrays → use 2 to ensure positive sums
          sb.Append("2");
        } else {
          // Even indices (excluding last), use 3 to maintain positivity of subarrays
          sb.Append("3");
        }
        if (i != n) {
          // Add space between elements except after last one
          sb.Append(' ');
        }
      }
      
      Console.WriteLine(sb.ToString()); // Output constructed array
    }
  }
}
}


// https://github.com/VaHiX/codeForces/