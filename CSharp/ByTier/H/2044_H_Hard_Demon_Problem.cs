// Problem: CF 2044 H - Hard Demon Problem
// https://codeforces.com/contest/2044/problem/H

/*
H. Hard Demon Problem
Time Complexity: O(n^2 + q) per test case
Space Complexity: O(n^2) per test case

Algorithms/Techniques:
- 2D prefix sums for efficient submatrix sum queries
- Preprocessing using 3D prefix sums to support range sum queries in O(1)
- For each query, compute the weighted sum using precomputed values

This problem requires fast handling of multiple queries on a 2D matrix.
It uses 3D prefix sums to store cumulative sums for rows, columns, and overall,
enabling constant-time range sum queries.

Each query computes:
∑_{i=1}^{|A|} A_i * i
where A is the flattened submatrix from (x1,y1) to (x2,y2).
*/

using System;
using System.Text;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    StringBuilder outputBuffer = new StringBuilder();
    while (t-- > 0) {
      int n, q;
      var inputs = Console.ReadLine().Split();
      n = int.Parse(inputs[0]);
      q = int.Parse(inputs[1]);
      long[,] M = new long[n, n];
      for (int r = 0; r < n; r++) {
        inputs = Console.ReadLine().Split();
        for (int c = 0; c < n; c++) {
          M[r, c] = long.Parse(inputs[c]);
        }
      }
      // Initialize 3D prefix sum arrays
      long[,] S = new long[n + 1, n + 1];   // overall sum
      long[,] Sr = new long[n + 1, n + 1];  // row-weighted sum
      long[,] Sc = new long[n + 1, n + 1];  // column-weighted sum
      for (int r = 1; r <= n; r++) {
        long current_S = 0;
        long current_Sr = 0;
        long current_Sc = 0;
        for (int c = 1; c <= n; c++) {
          long val = M[r - 1, c - 1];
          current_S += val;
          current_Sr += val * r;
          current_Sc += val * c;
          // Build 2D prefix sums for three arrays
          S[r, c] = S[r - 1, c] + current_S;
          Sr[r, c] = Sr[r - 1, c] + current_Sr;
          Sc[r, c] = Sc[r - 1, c] + current_Sc;
        }
      }
      for (int i = 0; i < q; i++) {
        var query = Console.ReadLine().Split();
        int x1 = int.Parse(query[0]);
        int y1 = int.Parse(query[1]);
        int x2 = int.Parse(query[2]);
        int y2 = int.Parse(query[3]);
        
        // Compute submatrix sums using inclusion-exclusion principle
        long S_sub =
            S[x2, y2] - S[x1 - 1, y2] - S[x2, y1 - 1] + S[x1 - 1, y1 - 1];
        long Sr_sub =
            Sr[x2, y2] - Sr[x1 - 1, y2] - Sr[x2, y1 - 1] + Sr[x1 - 1, y1 - 1];
        long Sc_sub =
            Sc[x2, y2] - Sc[x1 - 1, y2] - Sc[x2, y1 - 1] + Sc[x1 - 1, y1 - 1];
        
        // Calculate weighted sum using the formula
        int W = y2 - y1 + 1;
        long sum_val = (long)W * (Sr_sub - (long)x1 * S_sub) +
                       (Sc_sub - (long)(y1 - 1) * S_sub);
        outputBuffer.Append(sum_val).Append(' ');
      }
      Console.WriteLine(outputBuffer.ToString().Trim());
      outputBuffer.Clear();
    }
  }
}


// https://github.com/VaHiX/codeForces/