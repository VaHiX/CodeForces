// Problem: CF 2112 E - Tree Colorings
// https://codeforces.com/contest/2112/problem/E

/*
E. Tree Colorings

This problem involves finding the minimum number of vertices in a tree such that there are exactly m beautiful colorings.

Beautiful coloring rules:
1. Root is green
2. Blue and green vertices form a connected component (no yellow in between)
3. Yellow and green vertices form a connected component (no blue in between)

The algorithm uses dynamic programming with the following approach:
- For each vertex count m, compute the minimum number of vertices to achieve exactly m beautiful colorings
- Use recursive decomposition on divisors of m
- g[m] represents minimum vertices to generate exactly m beautiful colorings
- f[m] stores the result for final output

Time Complexity: O(M log M + T) where M = 5*10^5 and T is number of test cases
Space Complexity: O(M) for storing arrays and divisor lists

Algorithms/Techniques:
- Dynamic Programming with divisor decomposition
- Preprocessing all divisors up to M
- Recurrence relation based on factorization
*/

using System;
using System.Collections.Generic;
class Program {
  const int M = 500000;
  const long INF = (long)1e18;
  static void Main() {
    var div = new List<int>[M + 1];
    for (int i = 0; i <= M; i++)
      div[i] = new List<int>();
    // Precompute divisors for all numbers from 1 to M
    for (int i = 1; i <= M; i++) {
      for (int j = i; j <= M; j += i) {
        div[j].Add(i);
      }
    }
    long[] g = new long[M + 1];
    long[] f = new long[M + 1];
    // Initialize arrays with infinity
    for (int i = 0; i <= M; i++) {
      g[i] = INF;
      f[i] = INF;
    }
    // Base case: one beautiful coloring possible with just root vertex (green)
    g[1] = 0;
    f[1] = 1;
    
    // For each number from 2 to M, compute minimum vertices needed
    for (int m = 2; m <= M; m++) {
      // Case 1: Add two vertices to previous solution (g[m-2])
      if (m >= 3 && g[m - 2] < INF) {
        g[m] = Math.Min(g[m], 1 + g[m - 2]);
      }
      
      // Case 2: Decompose m using its divisors and sum up solutions
      foreach (int d in div[m]) {
        if (d < 3 || d == m)
          continue;
        if (m % d != 0)
          continue;
        int k = m / d;       // Compute the second factor
        int dVal = d - 2;    // Adjust for subtree decomposition
        if (dVal < 1)
          continue;
        // If both parts have valid solutions, update with better option
        if (g[dVal] < INF && g[k] < INF) {
          long cand = 1 + g[dVal] + g[k];
          if (cand < g[m]) {
            g[m] = cand;
          }
        }
      }
      // f[m] = 1 + g[m] because we add root vertex
      f[m] = 1 + g[m];
    }
    
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      int mVal = int.Parse(Console.ReadLine());
      if (mVal > M || f[mVal] >= INF) {
        Console.WriteLine(-1);
      } else {
        Console.WriteLine(f[mVal]);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/