// Problem: CF 2084 A - Max and Mod
// https://codeforces.com/contest/2084/problem/A

/*
 * Problem: A. Max and Mod
 * Algorithms/Techniques: Construction Algorithm
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 * 
 * Description:
 * Given an integer n, find a permutation of length n such that for all i from 2 to n,
 * max(p[i-1], p[i]) mod i = i - 1. If no such permutation exists, output -1.
 * 
 * Approach:
 * - For even n, it's impossible to construct such a permutation.
 * - For odd n:
 *   - Start with the sequence [n, 1, 2, ..., n-1]
 *   - This ensures max(p[i-1], p[i]) mod i = i - 1 for all valid i
 */

using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read current test case n
      getAns(n); // Process and output result for this n
    }
  }
  static void getAns(int n) {
    if (n % 2 == 0) { // If n is even, no valid permutation exists
      Console.WriteLine(-1);
      return;
    }
    var ans = new List<int>() { n }; // Start the permutation with n
    for (int i = 1; i < n; i++) // Fill the rest of the permutation with 1 to n-1
      ans.Add(i);
    Console.WriteLine(string.Join(" ", ans)); // Output the permutation
  }
}


// https://github.com/VaHiX/codeForces/