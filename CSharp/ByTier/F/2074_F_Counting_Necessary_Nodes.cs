// Problem: CF 2074 F - Counting Necessary Nodes
// https://codeforces.com/contest/2074/problem/F

// F. Counting Necessary Nodes
// Problem: Given a rectangular region [l1, r1] × [l2, r2], find the minimum number of quadtree nodes needed to exactly cover it.
// Algorithm: 
//   1. Decompose each interval [l, r] into a sequence of intervals using bit manipulation and powers of two
//   2. For each such decomposition, compute the contribution of node overlaps in scoring function
// Time Complexity: O(log R) per test case where R <= 1e6
// Space Complexity: O(log R) due to storing decompositions

using System;
using System.Collections.Generic;

class Program {
  // Returns the largest power of two that does not exceed x
  static int LargestPowerOfTwo(int x) {
    int p = 1;
    while (p <= x) {
      p <<= 1; // Left shift to multiply by 2
    }
    return p >> 1; // Right shift to divide by 2, get the largest power of two <= x
  }

  // Decomposes interval [L, R] into segments based on powers of two
  static List<int> DecomposeInterval(int L, int R) {
    List<int> endpoints = new List<int> { L };
    int i = L;
    while (i < R) {
      int rem = R - i;
      int t;
      
      // Special treatment for starting point (0)
      if (i == 0) {
        t = LargestPowerOfTwo(rem);
      } else {
        // Use bitwise AND to extract lowest set bit
        t = i & -i;
        int candidate = LargestPowerOfTwo(rem);
        // Choose the smaller of the two: lowest bit or power of two
        if (t > candidate)
          t = candidate;
      }
      
      if (t <= 0)
        t = 1;
        
      if (i + t > R)
        t = rem;
        
      endpoints.Add(i + t);
      i += t;
    }
    return endpoints;
  }

  // Computes the required score based on differences in decomposed intervals
  static long ComputeScore(List<int> X, List<int> Y) {
    long ans = 0;
    for (int i = 0; i < X.Count - 1; i++) {
      int dx = X[i + 1] - X[i];
      for (int j = 0; j < Y.Count - 1; j++) {
        int dy = Y[j + 1] - Y[j];
        int mini = Math.Min(dx, dy);
        int maxi = Math.Max(dx, dy);
        // Add number of full divisions
        ans += maxi / mini;
      }
    }
    return ans;
  }

  static void ProcessTestCase() {
    string[] tokens = Console.ReadLine().Split();
    int l1 = int.Parse(tokens[0]);
    int r1 = int.Parse(tokens[1]);
    int l2 = int.Parse(tokens[2]);
    int r2 = int.Parse(tokens[3]);
    
    // Decompose both intervals
    List<int> X = DecomposeInterval(l1, r1);
    List<int> Y = DecomposeInterval(l2, r2);
    
    // Compute and output the final score
    long result = ComputeScore(X, Y);
    Console.WriteLine(result);
  }

  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int tc = 0; tc < t; tc++) {
      ProcessTestCase();
    }
  }
}


// https://github.com/VaHiX/codeForces/