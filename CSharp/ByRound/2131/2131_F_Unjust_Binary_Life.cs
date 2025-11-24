// Problem: CF 2131 F - Unjust Binary Life
// https://codeforces.com/contest/2131/problem/F

//  F. Unjust Binary Life
//  Purpose: Given two binary strings a and b of length n, this program computes the sum of minimum operations required for Yuri to reach each cell (x,y) in an n×n grid where grid[i][j] = a[i] XOR b[j]. Each operation allows flipping one bit in either string a or b. 

//  Algorithms/Techniques:
//   - Prefix sums
//   - Binary search
//   - Sorting
//   - Mathematical transformation of XOR to linear problem using 2 * prefix_sum - length

//  Time Complexity: O(n log n) per test case due to sorting and binary search.
//  Space Complexity: O(n) for storing arrays and prefix sums.

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Solve() {
    long n = long.Parse(Console.ReadLine());
    string a = Console.ReadLine();
    string b = Console.ReadLine();
    
    // Compute prefix sums for strings a and b
    var prefixA = new long[n + 1];
    var prefixB = new long[n + 1];
    for (int i = 0; i < n; i++) {
      prefixA[i + 1] = prefixA[i] + (a[i] - '0');
      prefixB[i + 1] = prefixB[i] + (b[i] - '0');
    }
    
    // Transform prefix sums into values for comparison
    var transA = new long[n];
    var transB = new long[n];
    for (int i = 0; i < n; i++) {
      transA[i] = 2 * prefixA[i + 1] - (i + 1); // Transformation of a prefix to value
      transB[i] = 2 * prefixB[i + 1] - (i + 1); // Same for b
    }
    
    // Sort the transformed values of b (for binary search later)
    Array.Sort(transB);
    
    // Compute prefix sums for sorted transB array
    var prefixSumB = new long[n + 1];
    for (int i = 0; i < n; i++)
      prefixSumB[i + 1] = prefixSumB[i] + transB[i];
      
    long totalSumB = prefixSumB[n]; // Total sum of transformed b values
    
    long absoluteSum = 0;
    
    // For each transformed value in a, compute contribution to the total
    foreach (var c in transA) {
      int splitIndex = Array.BinarySearch(transB, -c); // Find index where -c would be inserted
      if (splitIndex < 0)
        splitIndex = ~splitIndex; // Get insertion point
        
      long countGreater = n - splitIndex; // Count of elements in transB greater than -c
      long countLess = splitIndex;         // Count of elements less than -c
      
      // Add contribution to total sum based on positions
      absoluteSum += c * (countGreater - countLess) + totalSumB -
                     2 * prefixSumB[splitIndex];
    }
    
    // Calculate final result using derived formula
    long totalXY = n * n * (n + 1);
    long answer = (totalXY - absoluteSum) / 2;
    Console.WriteLine(answer);
  }
  
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/