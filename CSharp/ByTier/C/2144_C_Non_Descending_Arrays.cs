// Problem: CF 2144 C - Non-Descending Arrays
// https://codeforces.com/contest/2144/problem/C

/*
 * Problem: Non-Descending Arrays
 * 
 * Algorithm/Technique: Dynamic Programming with State Compression
 * 
 * Time Complexity: O(n * 2 * 2 * 2) = O(n), where n is the length of arrays
 * Space Complexity: O(n * 2) = O(n), for the DP table
 * 
 * The solution uses dynamic programming to count valid subsets of positions that can be swapped
 * such that both arrays remain sorted in non-descending order after the swaps.
 * 
 * Key idea: For each position i, we maintain two states:
 * - State 0: a[i] is used at this position
 * - State 1: b[i] is used at this position
 * 
 * We iterate forward through the array and update the DP table based on whether
 * swapping or not swapping at each step maintains the non-descending property.
 * 
 * At each step, for every previous valid state (0 or 1), we try both possibilities
 * (0 or 1) for the next element and check if the resulting order is valid.
 * 
 * Finally, sum up the valid states at the last position to get the total number of good subsets.
 */

using System;
using System.Linq;
public class Program {
  const int MOD = 998244353;
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int[] b = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int[,] dp = new int[n, 2]; // dp[i, s] represents number of ways to reach position i with state s (0 = use a[i], 1 = use b[i])
      dp[0, 0] = 1; // Initially, we can use a[0] in the first position
      dp[0, 1] = 1; // Initially, we can use b[0] in the first position
      for (int i = 0; i < n - 1; i++) {
        for (int s1 = 0; s1 < 2; s1++) {
          if (dp[i, s1] == 0)
            continue; // Skip if no way to reach this state
          int currentA = s1 == 0 ? a[i] : b[i]; // Value from a or b at current position
          int currentB = s1 == 0 ? b[i] : a[i]; // The other value (after potential swap)
          for (int s2 = 0; s2 < 2; s2++) {
            int nextA = s2 == 0 ? a[i + 1] : b[i + 1]; // Value from a or b at next position
            int nextB = s2 == 0 ? b[i + 1] : a[i + 1]; // The other value at next position
            // Check if both elements at this step will be in non-descending order when we move to next
            if (currentA <= nextA && currentB <= nextB) {
              dp[i + 1, s2] = (dp[i + 1, s2] + dp[i, s1]) % MOD;
            }
          }
        }
      }
      int ans = (dp[n - 1, 0] + dp[n - 1, 1]) % MOD; // Sum the number of ways to end at last position with either state
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/