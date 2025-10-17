// Problem: CF 1991 D - Prime XOR Coloring
// https://codeforces.com/contest/1991/problem/D

/// <summary>
/// This program solves the "Prime XOR Coloring" problem.
/// 
/// Problem Description:
/// Given an undirected graph with n vertices (numbered 1 to n), there is an edge between 
/// vertices u and v if and only if u ⊕ v (XOR) is a prime number.
/// We need to color the vertices using the minimum number of colors such that no two 
/// adjacent vertices share the same color.
/// 
/// Approach:
/// - The chromatic number (minimum colors needed) for this graph depends on the value of n.
/// - For small values of n, the chromatic number can be precomputed.
/// - For larger values of n, a cyclic coloring pattern is used where colors repeat in a cycle.
/// 
/// Time Complexity: O(1) for each test case, since we're using a precomputed map and 
/// constant-time operations.
/// Space Complexity: O(1) for the precomputed maps and lists, as they are fixed-size.
/// </summary>

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int chromaticNumber = FindChromaticNumber(n);
      List<long> colors = new List<long>();
      AssignColors(n, chromaticNumber, colors);
      Console.WriteLine(chromaticNumber);
      for (int i = 0; i < colors.Count; i++) {
        if (i > 0)
          Console.Write(" ");
        Console.Write(colors[i]);
      }
      Console.WriteLine();
    }
  }
  
  /// <summary>
  /// Returns the chromatic number for the given number of vertices n.
  /// The chromatic number is the minimum number of colors required to color the graph.
  /// This method uses a precomputed map for small inputs.
  /// </summary>
  static int FindChromaticNumber(int n) {
    var chromaticMap =
        new Dictionary<int, int> { { 1, 1 }, { 2, 2 }, { 3, 2 },
                                   { 4, 3 }, { 5, 3 }, { 6, 4 } };
    return chromaticMap.ContainsKey(n) ? chromaticMap[n] : 4;
  }
  
  /// <summary>
  /// Assigns colors to each vertex based on the chromatic number.
  /// For small n, uses a precomputed color pattern.
  /// For larger n, uses a cyclic color assignment.
  /// </summary>
  static void AssignColors(int n, int chromaticNumber, List<long> colors) {
    var colorPatterns = new Dictionary<int, List<long>> {
      { 1, new List<long> { 1 } },
      { 2, new List<long> { 1, 2 } },
      { 3, new List<long> { 1, 2, 2 } },
      { 4, new List<long> { 1, 2, 2, 3 } },
      { 5, new List<long> { 1, 2, 2, 3, 3 } },
      { 6, new List<long> { 1, 2, 2, 3, 3, 4 } }
    };
    if (colorPatterns.ContainsKey(n)) {
      colors.AddRange(colorPatterns[n]);
    } else {
      int currentColor = 1;
      for (int i = 1; i <= n; ++i) {
        colors.Add(currentColor);
        currentColor = (currentColor % chromaticNumber) + 1;
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/