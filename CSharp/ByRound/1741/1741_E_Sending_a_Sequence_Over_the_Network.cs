// Problem: CF 1741 E - Sending a Sequence Over the Network
// https://codeforces.com/contest/1741/problem/E

/*
 * Problem: Sending a Sequence Over the Network
 * 
 * Algorithm: Dynamic Programming with Index Tracking
 * 
 * Approach:
 * - We model the problem as a graph traversal where each element in the array b
 *   represents either a segment length (which we can use to jump forward) or
 *   a segment of values that we need to reconstruct.
 * - For each element b[i], if it's a segment length, we can either:
 *   1. Use it to jump backward (i - b[i]) if the previous state is valid
 *   2. Use it to jump forward (i + 1 + b[i]) if within bounds
 * - We use a boolean DP array to track whether we can reach index i.
 * 
 * Time Complexity: O(n), where n is the length of the sequence b.
 * Space Complexity: O(n), for the DP array.
 */

using System;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] xs = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      bool[] dp = new bool[n + 1]; // dp[i] indicates if we can reach the i-th position
      dp[0] = true; // Base case: we start at position 0
      
      for (int i = 0; i < n; i++) {
        // If dp[i] is true, then we can process element at index i
        // Try jumping backward using the value at xs[i]
        if (i - xs[i] >= 0) {
          dp[i + 1] |= dp[i - xs[i]]; // Update dp[i+1] if we can jump from i-xs[i]
        }
        
        // Try jumping forward using the value at xs[i]
        if (i + xs[i] < n) {
          dp[i + 1 + xs[i]] |= dp[i]; // Update dp[i+1+xs[i]] if we can jump from i
        }
      }
      
      // Check if we can reach the end of the sequence
      Console.WriteLine(dp[n] ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/CodeForces/