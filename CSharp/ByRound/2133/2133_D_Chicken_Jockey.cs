// Problem: CF 2133 D - Chicken Jockey
// https://codeforces.com/contest/2133/problem/D

/*
 * Problem: Chicken Jockey (D)
 * 
 * Description:
 * A chicken jockey consists of n mobs stacked vertically. Each mob has health h[i].
 * Steve can deal 1 damage to any mob per attack. When a mob's health drops to 0 or less:
 *   - It dies.
 *   - All mobs above it fall down forming a new stack.
 *   - The bottom mob in the new stack takes fall damage equal to the number of mobs below it.
 * Goal: Find minimum number of attacks to kill all mobs.
 * 
 * Approach:
 * Dynamic Programming with states representing transitions as mobs die and fall,
 * keeping track of optimal path using memoization. The key insight is to model
 * falling behavior using a DP state that considers how many falls are required
 * for the current subproblem.
 * 
 * Complexity:
 * Time: O(n)
 * Space: O(n)
 */

using System.Text;

namespace ChickenJockey;
class Program {
  static long Solve() {
    int n = Next();
    int[] a = new int[n];
    for (int i = 0; i < n; i++)
      a[i] = Next();
    
    // last[i]: index of the next non-dead mob after i, or n if none
    int[] last = new int[n];
    if (a[^1] == 1)
      last[^1] = last.Length - 1;
    else
      last[^1] = last.Length;
    for (int i = a.Length - 2; i >= 0; i--) {
      if (a[i] != 1)
        last[i] = i;
      else
        last[i] = last[i + 1];
    }
    
    // dp[i, 0]: Min attacks to clear stack starting at i with current bottom alive and no fall damage
    // dp[i, 1]: Min attacks with current bottom possibly having fall damage applied
    // dp[i, 2]: Min attacks when the previous state is considered as fall damage case
    long[,] dp = new long[n + 1, 3];
    
    // Base case: last element
    dp[n - 1, 0] = a[^1];
    dp[n - 1, 1] = a[^1];
    dp[n - 1, 2] = 0;

    for (int i = a.Length - 2; i >= 0; i--) {
      // State transition 0: attacking current mob
      dp[i, 0] = a[i] + dp[i + 1, 0];
      // If next mob can be directly attacked without fall, consider that path (fall-free)
      if (a[i + 1] <= i + 1)
        dp[i, 0] = Math.Min(dp[i, 0], a[i] + dp[i + 1, 2]);
      else {
        // Otherwise, account for some fall damage from previous
        dp[i, 0] = Math.Min(dp[i, 0], a[i] + dp[i + 1, 1] - i - 1);
      }

      // State transition 1: this may lead to fall
      dp[i, 1] = a[i] + dp[i + 1, 0];
      if (a[i + 1] < 2)
        dp[i, 1] = Math.Min(dp[i, 1], a[i] + dp[i + 1, 2]);
      else {
        dp[i, 1] = Math.Min(dp[i, 1], a[i] + dp[i + 1, 1] - 1);
      }

      // State transition 2: previous move was fall
      dp[i, 2] = dp[i + 1, 0];
      if (a[i + 1] < 2)
        dp[i, 2] = Math.Min(dp[i, 2], dp[i + 1, 2]);
      else {
        dp[i, 2] = Math.Min(dp[i, 2], dp[i + 1, 1] - 1);
      }
    }
    
    return dp[0, 0];
  }

  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve());
    writer.Flush();
  }

  static int Next() {
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/