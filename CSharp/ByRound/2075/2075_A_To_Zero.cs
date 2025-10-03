// Problem: CF 2075 A - To Zero
// https://codeforces.com/contest/2075/problem/A

/*
 * Problem: A. To Zero
 * Purpose: Given two integers n and k (k is an odd number >= 3), 
 *          find the minimum number of operations to reduce n to 0.
 *          Each operation allows subtracting a value x from 1 to k,
 *          with the constraint that x must have the same parity as n.
 *          
 * Algorithm:
 * - If n is even and k is even: use k (since both are even, all valid x are even)
 * - If n is even and k is odd: use k-1 (to ensure we can always choose even x to match n's parity)
 * - If n is odd and k is even: subtract k-1 first to make it even; then proceed with k
 * - If n is odd and k is odd: subtract k first, then proceed with k-1
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n and k
      var n = int.Parse(line[0]);
      var k = int.Parse(line[1]);
      getAns(n, k); // Compute answer for current test case
    }
  }

  // Helper function to calculate ceiling division of (n + k - 1) / k
  static int ee(int n, int k) => (n + k - 1) / k;

  static void getAns(int n, int k) {
    int ans;
    if (n % 2 == 0) { // If n is even
      if (k % 2 == 0) // If k is also even
        ans = ee(n, k); // Use k directly
      else // If k is odd
        ans = ee(n, k - 1); // Use k-1 to match parity
    } else { // If n is odd
      if (k % 2 == 0) { // If k is even
        n -= k - 1; // Subtract k-1 first to make it even
        if (n <= 0)
          ans = 1; // Already done in one step
        else
          ans = ee(n, k) + 1; // Continue with k and add one operation
      } else { // If k is odd
        n -= k; // Subtract k first to make it even
        if (n <= 0)
          ans = 1; // Already done in one step
        else
          ans = ee(n, k - 1) + 1; // Continue with k-1 and add one operation
      }
    }
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/