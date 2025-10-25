// Problem: CF 1899 C - Yarik and Array
// https://codeforces.com/contest/1899/problem/C

/*
 * Problem: Yarik and Array
 * Purpose: Find the maximum sum of a subarray where adjacent elements have alternating parities.
 * Algorithm: Modified Kadane's Algorithm with parity check
 * Time Complexity: O(n) - Single pass through the array
 * Space Complexity: O(n) - For storing the array elements
 * 
 * Techniques:
 * - Kadane's algorithm variant for maximum subarray sum
 * - Parity check using modulo operator (% 2)
 * - Dynamic adjustment of current sum based on parity constraint
 */

using System;
public class YarikAndArray {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      short[] a = new short[n];
      for (int j = 0; j < n; j++)
        a[j] = short.Parse(parts[j]);
      int sum = a[0];  // Initialize current sum with first element
      int ans = a[0];  // Initialize maximum sum found so far
      for (int j = 1; j < n; j++) {
        // If current sum is negative or adjacent elements have same parity, reset sum to 0
        if (sum < 0 || Math.Abs(a[j]) % 2 == Math.Abs(a[j - 1]) % 2)
          sum = 0;
        sum += a[j];  // Add current element to the sum
        ans = Math.Max(ans, sum);  // Update maximum sum if current sum is greater
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/