// Problem: CF 1979 A - Guess the Maximum
// https://codeforces.com/contest/1979/problem/A

/*
 * Problem: Guess the Maximum
 * 
 * Purpose: 
 *   Given an array of integers, Alice chooses a value k and Bob selects a subarray.
 *   If the maximum element in Bob's chosen subarray is strictly greater than k, Alice wins.
 *   The task is to find the maximum k such that Alice is guaranteed to win regardless of Bob's choice.
 * 
 * Approach:
 *   - For Alice to be guaranteed to win, k must be less than the smallest maximum of any two adjacent elements.
 *   - Because if k is less than the minimum of all adjacent maxima, then no matter which subarray Bob picks,
 *     its maximum will always be greater than k (since in the worst case, it contains at least one of the adjacent pairs).
 *   - So we compute the maximum of each pair of adjacent elements, find the minimum among these maxima,
 *     and subtract 1 to get the maximum value of k where Alice is guaranteed to win.
 * 
 * Time Complexity: O(n)
 *   - We iterate through the array once to compute adjacent maxima and find the minimum.
 * 
 * Space Complexity: O(1)
 *   - Only a constant amount of extra space is used.
 */
using System;
using System.Collections.Generic;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()); // Read size of array
      List<long> arr = new List<long>();
      string[] input = Console.ReadLine().Split(' ');
      for (int i = 0; i < n; i++) {
        arr.Add(long.Parse(input[i])); // Read array elements
      }
      long mn = long.MaxValue; // Initialize minimum of adjacent maxima to maximum value
      for (int i = 0; i < n - 1; i++) {
        long mx = long.MinValue;
        mx = Math.Max(arr[i], arr[i + 1]); // Find maximum of adjacent pair
        mn = Math.Min(mn, mx); // Keep track of minimum of all such maxima
      }
      Console.WriteLine(mn - 1); // Output the maximum k where Alice is guaranteed to win
    }
  }
}


// https://github.com/VaHiX/CodeForces/