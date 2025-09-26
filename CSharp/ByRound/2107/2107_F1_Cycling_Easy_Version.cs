// Problem: CF 2107 F1 - Cycling (Easy Version)
// https://codeforces.com/contest/2107/problem/F1

/*
 * Problem: F1. Cycling (Easy Version)
 * 
 * Purpose:
 *   This program computes the minimum cost for Leo to move from behind the n-th cyclist 
 *   to in front of the 1-st cyclist on a road where cyclists are arranged in a line.
 *   
 *   The key operations allowed are:
 *     - Move in front of a cyclist (cost = agility value of that cyclist)
 *     - Swap two elements (cost = index difference)
 *   
 *   The strategy uses dynamic programming to optimize the sequence of swaps and moves.
 *   
 * Algorithms/Techniques Used:
 *   - Dynamic Programming (DP)
 *   - Greedy selection for minimum agility in a range
 *   
 * Time Complexity: O(n^3)  
 *   - Outer loop over n elements.
 *   - Inner loops for finding minimum agility and computing DP values.
 *   - Finding p (minimum element) within [i+1, n] → O(n).
 *   - DP transitions within [p, n] → O(n).
 *   
 * Space Complexity: O(n)
 *   - Storage for arrays: agility[], dp[].
 */

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var a = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int[] agility = new int[n + 1]; // Store agility values indexed from 1
      for (int i = 1; i <= n; i++) {
        agility[i] = a[i - 1];
      }
      long[] dp = new long[n + 1]; // dp[i]: minimum cost to reach position i
      for (int i = 0; i <= n; i++)
        dp[i] = long.MaxValue;
      dp[n] = 0; // Base case: at the last cyclist, cost is 0
      
      // Process positions from back to front
      for (int i = n - 1; i >= 0; i--) {
        int p = i + 1; // Find minimum agility in range [i+1, n]
        for (int j = i + 1; j <= n; j++) {
          if (agility[j] < agility[p])
            p = j;
        }
        // For each valid position j >= p, calculate transition cost
        for (int j = p; j <= n; j++) {
          long swapCost = 2L * (j - p); // Cost of swapping to bring element at p to position j
          long overtakeCost = (long)(j - i) * agility[p]; // Cost of moving behind p
          long moveCost = (p - i - 1); // Additional moves needed before this swap
          dp[i] = Math.Min(dp[i], dp[j] + swapCost + overtakeCost + moveCost);
        }
      }
      Console.WriteLine(dp[0]);
    }
  }
}


// https://github.com/VaHiX/codeForces/