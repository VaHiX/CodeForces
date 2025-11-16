// Problem: CF 1767 B - Block Towers
// https://codeforces.com/contest/1767/problem/B

using System;
using System.Text;
public class BlockTowers {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] a = new int[n];
      for (int j = 0; j < n; j++)
        a[j] = int.Parse(parts[j]);
      int ansi = a[0]; // Initialize result with the first tower's blocks
      Array.Sort(a); // Sort the array to process from smallest to largest
      int aMax = a[n - 1]; // Get the maximum value after sorting
      for (int j = 0; j < n && ansi < aMax; j++) // Loop through sorted array while ansi is less than max
        if (a[j] > ansi) { // If current element is greater than ansi
          int d = a[j] - ansi; // Calculate difference
          // Add half of the difference (rounded up) to ansi
          ansi += (d % 2 == 0 ? d / 2 : (d + 1) / 2);
        }
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}
/*
Algorithm: Greedy + Sorting
Time Complexity: O(n log n) due to sorting; O(n) for the loop, so overall O(n log n)
Space Complexity: O(n) for the array and auxiliary variables

Approach:
1. Sort the array to process elements from smallest to largest.
2. Start with the first tower's block count as the initial result.
3. For each element in the sorted array, if it's greater than current result:
   - Calculate the difference between the element and current result.
   - Add half the difference (rounded up) to the result to simulate moving blocks.
4. Continue until result is no longer less than the maximum element.
*/

// https://github.com/VaHiX/CodeForces/