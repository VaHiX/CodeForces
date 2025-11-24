// Problem: CF 2005 E1 - Subtangle Game (Easy Version)
// https://codeforces.com/contest/2005/problem/E1

/*
 * Problem: Subtangle Game (Easy Version)
 * Purpose: Determine the winner of a two-player game where players search for elements of an array in a matrix,
 *          following specific rules about movement and submatrix constraints.
 * 
 * Algorithm:
 * - Dynamic Programming with memoization (DFS + caching).
 * - State: f(i, j, k) represents whether the current player can win from position (i, j) in matrix and element k in array.
 * - Transition:
 *   1. Skip current cell: move to (i+1,j) or (i,j+1)
 *   2. Take current cell: if it matches current array element, advance both indices
 * - Players alternate turns; Tsovak starts first.
 * 
 * Time Complexity: O(n * m * l)
 * Space Complexity: O(n * m * l)
 */

using System;
using System.Collections.Generic;
using System.IO;
class Program {
  static void Main() {
#if DEBUG
    Console.SetIn(new StreamReader("input.txt"));
    Console.SetOut(new StreamWriter("output.txt") { AutoFlush = true });
#endif
    int tt = int.Parse(Console.ReadLine());
    while (tt-- > 0) {
      string[] input = Console.ReadLine().Split();
      int l = int.Parse(input[0]);
      int n = int.Parse(input[1]);
      int m = int.Parse(input[2]);
      List<int> arr = new List<int>();
      string[] arrInput = Console.ReadLine().Split();
      foreach (var s in arrInput) {
        arr.Add(int.Parse(s));
      }
      int[][] g = new int [n][];
      for (int i = 0; i < n; i++) {
        g[i] = new int[m];
        string[] gInput = Console.ReadLine().Split();
        for (int j = 0; j < m; j++) {
          g[i][j] = int.Parse(gInput[j]);
        }
      }
      int[][][] dp = new int [n][][];
      for (int i = 0; i < n; i++) {
        dp[i] = new int [m][];
        for (int j = 0; j < m; j++) {
          dp[i][j] = new int[l];
          for (int k = 0; k < l; k++) {
            dp[i][j][k] = -1;
          }
        }
      }
      Func<int, int, int, int> f = null;
      f = (i, j, k) => {
        // Base case: if any dimension runs out, game ends
        if (i == n || j == m || k == l)
          return 0;
        
        // Memoization check
        if (dp[i][j][k] != -1)
          return dp[i][j][k];
          
        // Option 1: don't take the current cell, try next row or column
        int notTake = Math.Max(f(i + 1, j, k), f(i, j + 1, k));
        
        // Option 2: take the current cell if it matches array element
        int take = (g[i][j] == arr[k]) && (f(i + 1, j + 1, k + 1) == 0) ? 1 : 0;
        
        // Return 1 if either option leads to winning state, else 0 loss
        return dp[i][j][k] = (notTake != 0 || take != 0) ? 1 : 0;
      };
      Console.WriteLine(f(0, 0, 0) != 0 ? "T" : "N");
    }
  }
}


// https://github.com/VaHiX/codeForces/