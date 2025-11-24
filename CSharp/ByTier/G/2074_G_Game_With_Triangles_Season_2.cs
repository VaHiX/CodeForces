// Problem: CF 2074 G - Game With Triangles: Season 2
// https://codeforces.com/contest/2074/problem/G

/*
G. Game With Triangles: Season 2
Algorithm: Dynamic Programming on intervals
Time Complexity: O(n^3), where n is the number of vertices
Space Complexity: O(n^2), for the DP table

The problem involves selecting non-overlapping triangles from a polygon such that the sum of products of vertex values is maximized.
This is solved using interval dynamic programming where dp[i,j] represents the maximum score achievable for the subpolygon from vertex i to j,
ensuring no triangles overlap in the interior.
*/

using System;
using System.Linq;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = new int[n + 1];
      string[] tokens = Console.ReadLine().Split();
      for (int i = 1; i <= n; i++) {
        a[i] = int.Parse(tokens[i - 1]);
      }
      long[,] dp = new long[n + 1, n + 1];
      for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
          int j = i + len - 1;
          if (len < 3) { // A triangle requires at least 3 vertices
            dp[i, j] = 0;
            continue;
          }
          long best = Math.Max(dp[i + 1, j], dp[i, j - 1]); // Base case: consider removing one vertex from either end
          
          // Try all possible middle vertices to form a triangle between i and j
          for (int m = i + 1; m < j; m++) {
            long tmp = 0;
            if (i + 1 <= m - 1)
              tmp += dp[i + 1, m - 1]; // Add the score from left subpolygon
            if (m + 1 <= j - 1)
              tmp += dp[m + 1, j - 1]; // Add the score from right subpolygon
            tmp += (long)a[i] * a[m] * a[j]; // Add triangle formed by i, m, j
            best = Math.Max(best, tmp);
          }
          
          // Also consider splitting the interval into two parts and solving recursively
          for (int k = i; k < j; k++) {
            best = Math.Max(best, dp[i, k] + dp[k + 1, j]);
          }
          dp[i, j] = best;
        }
      }
      Console.WriteLine(dp[1, n]);
    }
  }
}


// https://github.com/VaHiX/codeForces/