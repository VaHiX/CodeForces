// Problem: CF 2027 B - Stalin Sort
// https://codeforces.com/contest/2027/problem/B

/*
Purpose: This code solves the "Stalin Sort" problem where we need to find the minimum number of elements to remove from an array to make it "vulnerable". An array is vulnerable if it can be sorted in non-increasing order by repeatedly applying Stalin Sort on subarrays.

Algorithm: The solution uses a greedy approach based on tracking the maximum elements and their positions. It iteratively removes elements from the end and calculates the minimum deletions needed to make the array non-increasing.

Time Complexity: O(n^2) - In the worst case, for each element we might perform operations on a list of indices.
Space Complexity: O(n) - For storing the SortedList of elements and their indices.
*/

using System;
using System.Collections.Generic;
public class StalinSort {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      short n = short.Parse(Console.ReadLine()); // Read size of array
      string[] parts = Console.ReadLine().Split(); // Read array elements
      SortedList<int, List<short>> maxs = new SortedList<int, List<short>>(); // Store elements and their indices in sorted order
      for (short j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]); // Current element
        if (!maxs.ContainsKey(aj))
          maxs.Add(aj, new List<short>(new[] { j })); // Add new element with its index
        else
          maxs[aj].Add(j); // Add index to existing element's list
      }
      short countDelMax = 0; // Count of elements removed from max
      short countDelBeforeMax = 0; // Count of elements removed before max
      short ans = n; // Initialize answer with full array size
      do {
        countDelBeforeMax = // Calculate elements deleted before current max
            Convert.ToInt16(countDelMax + maxs.Values[maxs.Count - 1][0]);
        countDelMax++; // Increment max deletion counter
        ans = Math.Min(ans, countDelBeforeMax); // Update minimum deletions
        maxs.Values[maxs.Count - 1].RemoveAt(0); // Remove the first occurrence of max
        if (maxs.Values[maxs.Count - 1].Count == 0) // If no occurrences left
          maxs.RemoveAt(maxs.Count - 1); // Remove the entry
      } while (maxs.Count > 0 && ans > countDelMax); // Continue while data exists and improvement is possible
      Console.WriteLine(ans); // Output the result
    }
  }
}


// https://github.com/VaHiX/CodeForces/