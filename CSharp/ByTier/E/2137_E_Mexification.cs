// Problem: CF 2137 E - Mexification
// https://codeforces.com/contest/2137/problem/E

/*
E. Mexification
Algorithm: Simulation with MEX computation optimization
Time Complexity: O(n) per test case (amortized over k operations)
Space Complexity: O(n)

The problem involves applying a transformation k times where each element is replaced by the MEX of all other elements.
We optimize by observing patterns in the behavior of MEX after multiple iterations:
- If there exists an element that occurs at least twice, we can derive a pattern for large values of k.
- Otherwise, the sequence stabilizes to predictable values based on the first M elements.

Approach:
1. For each test case:
   - Read n and k
   - Count frequencies of elements in array up to n
   - Compute M = smallest index where frequency is 0 (i.e., first missing element)
   - Special case for k=1: direct MEX calculation of unique elements
   - For k>1:
     - If there's a repeated value, use mathematical formula based on repeated minimum
     - Else calculate using stable MEX behavior pattern
*/

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()!);
    while (t-- > 0) {
      var parts = Console.ReadLine()!.Split();
      int n = int.Parse(parts[0]);
      long k = long.Parse(parts[1]);
      int[] a = Console.ReadLine()!.Split().Select(int.Parse).ToArray();
      int[] freq = new int[n + 1];
      foreach (var val in a) {
        if (val <= n)
          freq[val]++;
      }
      int M = 0;
      while (M <= n && freq[M] > 0)
        M++;
      long SumAfterK1() {
        long sum = 0;
        int uniqueCount = 0;
        for (int y = 0; y < M; y++) {
          if (freq[y] == 1) { // If element occurs only once
            uniqueCount++;
            sum += y;
          }
        }
        return sum + (long)(n - uniqueCount) * M; // Remaining elements contribute M each
      }
      if (k == 1) {
        Console.WriteLine(SumAfterK1());
        continue;
      }
      int p = -1;
      for (int y = 0; y < M; y++) {
        if (freq[y] >= 2) { // Find first element that appears at least twice
          p = y;
          break;
        }
      }
      long ans;
      if (p != -1) {
        // Precompute sum of arithmetic sequence up to p
        long S = (long)p * (p - 1) / 2;
        long r = n - p; // Elements larger than p
        // Determine value contributed based on whether k is even or odd
        ans = (k % 2 == 0) ? S + r * p : S + r * (p + 1);
      } else {
        // All elements in [0, M) were unique. We know how this behaves.
        long S = (long)M * (M - 1) / 2;
        long r = n - M;
        if (r == 0) {
          ans = S;
        } else if (r == 1) {
          ans = S + M;
        } else {
          // k is large, so use parity of k to decide final value
          ans = (k % 2 == 0) ? S + r * (M + 1) : S + r * M;
        }
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/