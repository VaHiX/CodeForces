// Problem: CF 2070 D - Tree Jumps
// https://codeforces.com/contest/2070/problem/D

/*
 * Problem: D. Tree Jumps
 * 
 * Purpose: Calculate the number of valid vertex sequences in a rooted tree where
 *          each move from vertex v to u must satisfy d[u] = d[v] + 1, and if v is not root,
 *          then u cannot be a neighbor of v.
 *
 * Algorithm:
 * - For each node, compute its depth relative to the root.
 * - Count how many nodes exist at each depth level.
 * - Use dynamic programming on depths to calculate valid sequences:
 *   S[d] = count of valid sequences starting from a node at depth d,
 *          where we consider all possible extensions with appropriate constraints.
 * - The final answer is 1 (for the empty sequence) plus contribution from deepest level.
 *
 * Time Complexity: O(n) per test case, since we process each node once for depth and once for DP.
 * Space Complexity: O(n) for storing depth array, count array, and sum array.
 */

using System;
class Program {
  const int MOD = 998244353;
  static void Main() {
    string[] input = Console.In.ReadToEnd().Split(
        new[] { ' ', '\t', '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);
    int ptr = 0;
    int t = int.Parse(input[ptr++]);
    for (int testCase = 0; testCase < t; testCase++) {
      int n = int.Parse(input[ptr++]);
      if (n == 1) {
        Console.WriteLine("1");
        continue;
      }
      int[] parents = new int[n - 1];
      for (int i = 0; i < n - 1; i++) {
        parents[i] = int.Parse(input[ptr++]);
      }
      int[] depth = new int[n + 1];
      depth[1] = 0;
      int maxDepth = 0;
      for (int i = 2; i <= n; i++) {
        int p = parents[i - 2];
        depth[i] = depth[p] + 1;
        if (depth[i] > maxDepth)
          maxDepth = depth[i];
      }
      long[] cnt = new long[maxDepth + 1];
      for (int i = 2; i <= n; i++) {
        cnt[depth[i]]++;
      }
      long[] S = new long[maxDepth + 2];
      if (maxDepth >= 1) {
        S[maxDepth] = cnt[maxDepth] % MOD;
        for (int d = maxDepth - 1; d >= 1; d--) {
          // Factor represents number of choices from depth d, minus one for self-avoidance
          long factor = (cnt[d] - 1 + MOD) % MOD;
          S[d] = (cnt[d] % MOD + (factor * S[d + 1]) % MOD) % MOD;
        }
      }
      // Add 1 for the empty sequence, then add contributions from valid paths starting at depth 1
      long result = (1 + (maxDepth >= 1 ? S[1] : 0)) % MOD;
      Console.WriteLine(result);
    }
  }
}


// https://github.com/VaHiX/codeForces/