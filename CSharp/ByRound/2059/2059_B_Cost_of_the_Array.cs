// Problem: CF 2059 B - Cost of the Array
// https://codeforces.com/contest/2059/problem/B

/*
 * Problem: B. Cost of the Array
 * Purpose: To find the minimum cost of array b obtained by splitting array a into k subarrays,
 *          concatenating even-indexed (1-based) subarrays, appending 0, and finding the first index where b[i] != i.
 * Algorithms/Techniques:
 *   - Greedy approach with case analysis based on n and k values
 *   - Direct simulation of subarray partitioning logic
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for input array storage
 */

using System;
using System.Collections.Generic;

public class MyDemo {
  public static void solve() {
    string[] input = Console.ReadLine().Split();
    int n = int.Parse(input[0]);
    int k = int.Parse(input[1]);
    int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    
    // Special case when n == k: each element forms its own subarray
    if (n == k) {
      for (int i = 1; i < n; i += 2) {
        // For even indices in original array, check if they match expected value
        if (a[i] != (i + 1) / 2) {
          Console.WriteLine(i / 2 + 1);
          return;
        }
      }
      // If all checks passed, answer is n/2 + 1
      Console.WriteLine(n / 2 + 1);
      return;
    }
    
    // General case: iterate from end to start looking for conflicts
    for (int i = n - 1; i >= 1; i--) {
      int x = 2 + n - 1 - i;
      // If position is beyond k, check if a[i] == 1, otherwise cost is 1
      if (x >= k) {
        if (a[i] != 1) {
          Console.WriteLine(1);
          return;
        }
      }
    }
    
    // Default case, output 2
    Console.WriteLine(2);
  }
  
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/