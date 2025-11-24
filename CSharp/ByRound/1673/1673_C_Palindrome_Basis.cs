// Problem: CF 1673 C - Palindrome Basis
// https://codeforces.com/contest/1673/problem/C

/*
 * Problem: C. Palindrome Basis
 * 
 * Purpose: Count the number of ways to express a given positive integer n as a sum of positive palindromic integers.
 * 
 * Approach:
 * - Generate all palindromic numbers up to 40000 (as n <= 40000).
 * - Use dynamic programming where dp[i, k] represents the number of ways to form sum i using palindromes up to the k-th palindrome.
 * 
 * Time Complexity: O(n * m) where n <= 40000 and m is the number of palindromes (approximately 4000).
 * Space Complexity: O(n * m) for the DP table.
 * 
 * Algorithms/Techniques:
 * - Pre-generation of palindromic numbers
 * - Dynamic Programming with inclusion-exclusion for multisets
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    List<int> bers = new List<int>();
    
    // Generate all palindromic numbers up to 40000
    for (int i = 0; i < 10; i++) {
      bers.Add(i);
      bers.Add(i * 11);
      for (int j = 1; j < 10; j++) {
        bers.Add(j * 101 + i * 10);
        bers.Add(j * 1001 + i * 110);
        for (int k = 0; k < 10; k++) {
          bers.Add(j * 10001 + k * 1010 + i * 100);
        }
      }
    }
    
    // Filter valid palindromes, remove duplicates, sort
    bers = bers.Where(i => i <= 40000 && i > 0)
               .Distinct()
               .OrderBy(i => i)
               .ToList();
    
    // Initialize DP table
    long[,] dp = new long[40001, bers.Count];
    
    // Base case: there is one way to form sum 0 using no palindromes (empty set)
    dp[0, 0] = 0;
    
    // Base case: there is one way to form any sum using only 1 (all 1s)
    for (int i = 1; i <= 40000; i++)
      dp[i, 0] = 1;
    
    // Fill DP table
    for (int k = 1; k < bers.Count; k++) {
      for (int i = 1; i <= 40000; i++) {
        if (i - bers[k] >= 0) {
          // Include or exclude current palindrome
          dp[i, k] = (dp[i, k - 1] + dp[i - bers[k], k]);
          
          // Add 1 if the palindrome itself equals the sum (this corresponds to the set {palindrome})
          if (bers[k] == i)
            dp[i, k] += 1;
          
          dp[i, k] %= 1000000007; // Modulo operation
        } else {
          // If current palindrome is greater than sum, don't include it
          dp[i, k] = dp[i, k - 1];
        }
      }
    }
    
    // Process queries
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      long o = 0;
      try {
        o = dp[n, bers.Count - 1]; // Final answer for sum n using all palindromes
      } catch {
        o = n; // fallback (should not happen if input is correct)
      }
      output.Add(o.ToString());
    }
    
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/