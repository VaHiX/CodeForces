// Problem: CF 1863 B - Split Sort
// https://codeforces.com/contest/1863/problem/B

using System;
public class SplitSort {
  /*
   * Code Purpose:
   * This program determines the minimum number of operations needed to sort a permutation
   * by repeatedly splitting the array based on a pivot value x and reordering elements.
   * 
   * Algorithm:
   * 1. For each element p[i], we find its original index and store in idxs array.
   * 2. We sort the permutation p and maintain the mapping of original indices in idxs.
   * 3. Count how many times a previous element's original index is greater than the current one.
   *    This count represents the number of split operations needed.
   * 
   * Time Complexity: O(n log n) due to sorting steps.
   * Space Complexity: O(n) for storing the permutation and index arrays.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] p = new int[n];
      int[] idxs = new int[n];
      for (int j = 0; j < n; j++) {
        p[j] = int.Parse(parts[j]); // Parse each element of the permutation
        idxs[j] = j;                // Store original indices
      }
      Array.Sort(p, idxs);          // Sort based on p values, keeping track of original indices in idxs
      int ans = 0;
      for (int j = 1; j < n; j++)
        if (idxs[j] < idxs[j - 1]) // If current index is smaller than previous, a split is required
          ans++;
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/