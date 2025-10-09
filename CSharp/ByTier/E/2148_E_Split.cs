// Problem: CF 2148 E - Split
// https://codeforces.com/contest/2148/problem/E

/*
 * Problem: E. Split
 * Algorithm: Sliding window technique with pre-processing of element frequencies
 * Time Complexity: O(n) per test case, where n is the size of array
 * Space Complexity: O(n) for storing counts and limits
 *
 * The task is to count "awesome" subarrays — those where we can distribute elements into k multisets such that each multiset contains exactly the same number of elements of each value.
 * Key insight:
 *   - For each element value v, total occurrences in a subarray must be divisible by k to assign equal count to each multiset.
 *   - We use sliding window to find all valid subarrays where each element's frequency doesn't exceed its limit (total occurrence / k).
 */

using System;
using System.Collections.Generic;

public class Program {
  public static void Main() {
    var input = Console.In.ReadToEnd().Split(
        new[] { ' ', '\n', '\r', '\t' }, StringSplitOptions.RemoveEmptyEntries);
    int idx = 0;
    int t = int.Parse(input[idx++]); // Read number of test cases
    for (int test = 0; test < t; test++) {
      int n = int.Parse(input[idx++]); // Read array size
      int k = int.Parse(input[idx++]); // Read k (number of multisets)
      int[] a = new int[n + 1]; // Array to store elements, 1-indexed
      for (int i = 1; i <= n; i++) {
        a[i] = int.Parse(input[idx++]); // Fill array with input values
      }
      int[] total = new int[n + 1]; // Count total occurrences of each element in the entire array
      for (int i = 1; i <= n; i++) {
        total[a[i]]++; // Increment count for value a[i]
      }
      bool possible = true;
      int[] limit = new int[n + 1]; // For each value, stores maximum allowed frequency in any valid subarray
      for (int i = 1; i <= n; i++) {
        if (total[i] > 0) {
          if (total[i] % k != 0) { // If not divisible by k, it's impossible to equally distribute
            possible = false;
            break;
          }
          limit[i] = total[i] / k; // Limit is total count divided by number of multisets
        }
      }
      if (!possible) {
        Console.WriteLine(0); // No valid subarrays exist due to impossible distribution
        continue;
      }
      int[] count = new int[n + 1]; // Current frequency in sliding window
      long ans = 0; // Result counter for awesome subarrays
      int left = 1; // Left pointer of sliding window
      for (int right = 1; right <= n; right++) {
        count[a[right]]++; // Add current element to sliding window
        while (count[a[right]] > limit[a[right]]) { // Shrink window until condition satisfied
          count[a[left]]--;
          left++;
        }
        ans += (right - left + 1L); // All subarrays ending at 'right' and starting from 'left' to 'right' are valid
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/