// Problem: CF 1842 C - Tenzing and Balls
// https://codeforces.com/contest/1842/problem/C

// Flowerbox
/*
Algorithm/Techniques: Dynamic Programming with Memoization
Time Complexity: O(n)
Space Complexity: O(n)

This problem uses dynamic programming to find the maximum number of balls that can be removed
by selecting pairs of balls with the same color and removing all elements between them (inclusive).
The solution tracks the maximum number of balls that can be removed up to each index using a DP array,
and maintains the best previous state for each color encountered.
*/
// Flowerbox

using System;
using System.Text;
class Program {
  static int Solution() {
    int MIN = Int32.MinValue;
    int n = int.Parse(Console.ReadLine());
    int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    int[] dp = new int[n + 1];        // dp[i] stores the maximum balls removed up to position i
    int[] dp2 = new int[n + 1];       // dp2[i] stores the best value for color i seen so far
    for (int i = 0; i < n + 1; ++i) {
      dp2[i] = MIN;                   // Initialize dp2 with minimum value
    }
    for (int i = 0; i < n; ++i) {
      // Calculate the maximum balls that can be removed ending at position i+1
      dp[i + 1] = Math.Max(dp[i], dp2[a[i]] != MIN ? i + dp2[a[i]] : MIN);
      // Update dp2 with the new best value for color a[i]
      dp2[a[i]] = Math.Max(dp2[a[i]], (-i + 1) + dp[i]);
    }
    return dp[n];                     // Return the maximum number of balls that can be removed
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Console.WriteLine(Solution());
    }
  }
}


// https://github.com/VaHiX/CodeForces/