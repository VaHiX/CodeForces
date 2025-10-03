// Problem: CF 2091 F - Igor and Mountain
// https://codeforces.com/contest/2091/problem/F

/*
F. Igor and Mountain

Purpose:
This code computes the number of valid climbing routes on a mountain grid where each route starts from the bottom row,
ends at the top row, moves vertically or diagonally within an arm span 'd', and satisfies constraints on holds per level.

Algorithm:
- Dynamic Programming (DP) with 2D prefix sums for efficient range queries.
- For each row, we calculate valid paths that can reach the current position considering holds in previous rows and allowed distances.
- Uses modular arithmetic to handle large numbers and prevent overflow.

Time Complexity: O(n * m)
Space Complexity: O(m)

*/
using System;
using System.Linq;
public class Solver {
  const long Mod = 998244353;
  static long M(long x) { return (x % Mod + Mod) % Mod; }
  static long M(long a, long b) { return ((a - b) % Mod + Mod) % Mod; }
  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      long[] input = Console.ReadLine().Split().Select(long.Parse).ToArray();
      long n = input[0];
      long m = input[1];
      long d = input[2];
      long ans = 0;
      long[] cur = new long[m + 1]; // Current row DP values
      long[] prev = new long[m + 1]; // Previous row DP values
      bool[,] v = new bool[n + 1, m + 1]; // Holds availability matrix (1-indexed)
      for (int i = 1; i <= n; i++) {
        string row = Console.ReadLine();
        for (int j = 1; j <= m; j++) {
          v[i, j] = (row[j - 1] != '#'); // Mark if hold exists at position (i,j)
        }
      }
      // Initialize first row prefix sums
      for (int i = 1; i <= m; i++) {
        prev[i] = prev[i - 1] + (v[1, i] ? 1L : 0L);
      }
      // Process first row to calculate initial states (valid holds considering arm span)
      for (int i = 1; i <= m; i++) {
        if (v[1, i]) {
          long count =
              M(prev[Math.Min(i + d, m)], prev[Math.Max(0L, i - d - 1)]);
          cur[i] = count;
        } else {
          cur[i] = 0;
        }
      }
      // Process rows from second to last
      for (int i = 2; i <= n; i++) {
        // Cumulative sum of current row for vertical range calculation
        for (int j = 1; j <= m; j++) {
          cur[j] += cur[j - 1];
          cur[j] = M(cur[j]);
        }
        // Update previous row based on possible connections from current positions
        for (int j = 1; j <= m; j++) {
          if (v[i, j]) {
            long count =
                M(cur[Math.Min(j + d - 1, m)], cur[Math.Max(0L, j - d)]);
            prev[j] = count;
          } else {
            prev[j] = 0;
          }
        }
        // Prefix sum for the previous row to enable fast range updates
        for (int j = 1; j <= m; j++) {
          prev[j] += prev[j - 1];
          prev[j] = M(prev[j]);
        }
        // Final update for current row based on updated previous values and arm span
        for (int j = 1; j <= m; j++) {
          if (v[i, j]) {
            long count =
                M(prev[Math.Min(j + d, m)], prev[Math.Max(0L, j - d - 1)]);
            cur[j] = count;
          } else {
            cur[j] = 0;
          }
        }
      }
      // Sum up all valid paths from the last row
      for (int j = 1; j <= m; j++) {
        ans += cur[j];
        ans = M(ans);
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/