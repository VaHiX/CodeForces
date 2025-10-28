// Problem: CF 2140 C - Ultimate Value
// https://codeforces.com/contest/2140/problem/C

/*
C. Ultimate Value
Algorithms/Techniques: Dynamic Programming, Prefix/Suffix Optimization, Game Theory

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves a game between Alice and Bob where they alternate turns trying to maximize/minimize the value of f(a) = cost + (a[0] - a[1] + a[2] - a[3] ...).
Each player can either end the game or swap two elements, adding (r - l) to cost.
Alice tries to maximize f(a), Bob tries to minimize it.
We use optimized prefix/suffix computations to determine optimal moves based on parity of positions.
*/

using System;
using System.Collections.Generic;
class Program {
  const long INF = (long)4e18;
  static void Solve() {
    int n = int.Parse(Console.ReadLine()!);
    var tokens = Console.ReadLine()!.Split(' ');
    long[] a = new long[n];
    for (int i = 0; i < n; i++) {
      a[i] = long.Parse(tokens[i]);
    }
    // Compute initial value of f(a) without any swaps
    long initialS = 0;
    for (int i = 0; i < n; i++) {
      if ((i + 1) % 2 != 0)
        initialS += a[i];
      else
        initialS -= a[i];
    }
    if (n == 1) {
      Console.WriteLine(initialS);
      return;
    }
    long maxResult = initialS;
    // Maximum possible cost from a single swap with odd length
    long maxParityCost = (n % 2 != 0) ? n - 1 : n - 2;
    maxResult = Math.Max(maxResult, initialS + maxParityCost);
    
    // Precompute minimum 2*a[i] + i for even indices (used for maximizing change)
    long[] minPrefix = new long[n];
    for (int i = 0; i < n; i++)
      minPrefix[i] = INF;
    if (0 % 2 == 0)
      minPrefix[0] = 2 * a[0] + 0;
    for (int i = 1; i < n; i++) {
      minPrefix[i] = minPrefix[i - 1];
      if (i % 2 == 0)
        minPrefix[i] = Math.Min(minPrefix[i], 2 * a[i] + i);
    }
    
    // Find best improvement for odd indices (swap with even index to minimize)
    long maxChange = -INF;
    for (int r = 1; r < n; r++) {
      if (r % 2 != 0 && minPrefix[r - 1] != INF) {
        long change = (2 * a[r] + r) - minPrefix[r - 1];
        maxChange = Math.Max(maxChange, change);
      }
    }

    // Precompute maximum 2*a[i] - i for odd indices (used for minimizing change)
    long[] maxPrefix = new long[n];
    for (int i = 0; i < n; i++)
      maxPrefix[i] = -INF;
    if (n > 1 && 1 % 2 != 0)
      maxPrefix[1] = 2 * a[1] - 1;
    for (int i = 2; i < n; i++) {
      maxPrefix[i] = maxPrefix[i - 1];
      if (i % 2 != 0)
        maxPrefix[i] = Math.Max(maxPrefix[i], 2 * a[i] - i);
    }

    // Find best improvement for even indices (swap with odd index to maximize)
    for (int r = 2; r < n; r++) {
      if (r % 2 == 0 && maxPrefix[r - 1] != -INF) {
        long change = maxPrefix[r - 1] - (2 * a[r] - r);
        maxChange = Math.Max(maxChange, change);
      }
    }
    
    // Update final result with best possible change
    if (maxChange > -INF)
      maxResult = Math.Max(maxResult, initialS + maxChange);
    Console.WriteLine(maxResult);
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine()!);
    while (t-- > 0) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/