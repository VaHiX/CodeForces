// Problem: CF 1904 B - Collecting Game
// https://codeforces.com/contest/1904/problem/B

/*
 * Problem: Collecting Game
 * 
 * Purpose: Given an array of positive integers, for each element, determine the maximum number of 
 *          remaining elements you can remove by first removing that element and setting your score 
 *          equal to its value, then using the score to remove elements in an optimal order.
 * 
 * Algorithm: 
 *  - For each index i, we simulate starting with score a[i], and greedily remove elements 
 *    that can be removed with current score, updating score as we go.
 *  - A key optimization is to process elements in increasing order of their values to avoid 
 *    recomputing the same logic multiple times.
 *  - We use sorting and prefix sums to determine how many elements can be removed efficiently.
 * 
 * Time Complexity: O(n log n) per test case due to sorting operations
 * Space Complexity: O(n) for storing arrays and indices
 */

using System;
public class CollectingGame {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] a = new int[n];
      int[] idxs = new int[n]; // Store original indices to map back results
      long sum = 0; // Prefix sum to keep track of elements we can choose from
      for (int j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]);
        a[j] = aj;
        idxs[j] = j;
        sum += aj;
      }
      // Sort array values and keep track of original indices
      Array.Sort(a, idxs);
      int[] ans = new int[n]; // Result array to store answers for each original index
      int countRem = n - 1; // Initially, all elements except current can be removed
      ans[n - 1] = countRem; // For largest element, we can remove all smaller elements
      // We process from larger elements to smaller ones so that we can adjust countRem appropriately
      for (int j = n - 2; j > -1; j--) {
        sum -= a[j + 1]; // Remove the next largest element from sum, because it's already considered
        // If remaining sum is less than current element, we can't remove all elements up to this point
        if (sum < a[j + 1])
          countRem = j; // Update how many elements we can remove (starting from current index)
        ans[j] = countRem; // Record number of elements we can remove
      }
      // Restore original order of answers by mapping back indices
      Array.Sort(idxs, ans);
      Console.WriteLine(string.Join(" ", ans));
    }
  }
}


// https://github.com/VaHiX/CodeForces/