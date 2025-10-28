// Problem: CF 2075 D - Equalization
// https://codeforces.com/contest/2075/problem/D

/*
D. Equalization

Algorithm: Dynamic Programming + Preprocessing
  - Precompute all possible (shiftX, shiftY) combinations and their minimum costs using DP.
  - For each test case, find the minimal cost among valid combinations where x >> shiftX == y >> shiftY.

Time Complexity: O(MAX_OP * SHIFT_MAX^2), where MAX_OP = 60, SHIFT_MAX = 60
Space Complexity: O(SHIFT_MAX^2), for storing DP table and combinations.

Approach:
  - Use dynamic programming to determine minimum cost of reaching shift values (i,j) by applying operations.
  - Each operation allows shifting x or y by k bits to the right, with a cost of 2^k.
  - All possible (shiftX, shiftY) pairs are precomputed to avoid recomputation for each query.
*/

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  const int SHIFT_MAX = 60;
  const int MAX_OP = 60;
  static void Main() {
    const ulong INF_COST = ulong.MaxValue;
    ulong[,] dp = new ulong[SHIFT_MAX + 1, SHIFT_MAX + 1];
    for (int i = 0; i <= SHIFT_MAX; i++) {
      for (int j = 0; j <= SHIFT_MAX; j++) {
        dp[i, j] = INF_COST;
      }
    }
    dp[0, 0] = 0;
    for (int op = 1; op <= MAX_OP; op++) {
      ulong[,] nextDp = (ulong[,])dp.Clone(); // Clone current DP state
      for (int i = 0; i <= SHIFT_MAX; i++) {
        for (int j = 0; j <= SHIFT_MAX; j++) {
          if (dp[i, j] == INF_COST)
            continue;
          // Try shifting x by op bits to the right
          if (i + op <= SHIFT_MAX) {
            nextDp[i + op, j] =
                Math.Min(nextDp[i + op, j], dp[i, j] + (1UL << op));
          }
          // Try shifting y by op bits to the right
          if (j + op <= SHIFT_MAX) {
            nextDp[i, j + op] =
                Math.Min(nextDp[i, j + op], dp[i, j] + (1UL << op));
          }
        }
      }
      dp = nextDp; // Update DP state for next iteration
    }
    List<(int shiftX, int shiftY, ulong cost)> combos =
        new List<(int, int, ulong)>();
    for (int i = 0; i <= SHIFT_MAX; i++) {
      for (int j = 0; j <= SHIFT_MAX; j++) {
        if (dp[i, j] != INF_COST) {
          combos.Add((i, j, dp[i, j]));
        }
      }
    }
    int T = int.Parse(Console.ReadLine());
    while (T-- > 0) {
      string[] inputs = Console.ReadLine().Split();
      ulong X = ulong.Parse(inputs[0]);
      ulong Y = ulong.Parse(inputs[1]);
      if (X == Y) {
        Console.WriteLine(0);
        continue;
      }
      ulong best = INF_COST;
      foreach (var combo in combos) {
        ulong newX = X >> combo.shiftX;
        ulong newY = Y >> combo.shiftY;
        if (newX == newY) {
          best = Math.Min(best, combo.cost);
        }
      }
      Console.WriteLine(best);
    }
  }
}


// https://github.com/VaHiX/codeForces/