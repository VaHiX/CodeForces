// Problem: CF 1903 A - Halloumi Boxes
// https://codeforces.com/contest/1903/problem/A

using System;
public class HalloumiBoxes {
  /*
   * Problem: Determine if an array can be sorted using reversals of subarrays of length at most k.
   * 
   * Algorithm:
   * - If k == 1, we can only reverse subarrays of length 1, meaning no changes can be made.
   *   So the array must already be sorted.
   * - If k > 1, we can perform any number of reversals. The key insight is that if k > 1,
   *   any permutation can theoretically be achieved using bubble-sort-like operations.
   *   However, since we want to determine if the array can be sorted at all, and k allows us to
   *   perform enough reversals to fully rearrange the array, we just need to check if it's already sorted.
   *   
   * Time Complexity: O(n) per test case
   * Space Complexity: O(n) for storing the array elements
   */
  
  public static void Main() {
    byte t = byte.Parse(Console.ReadLine()); // Read number of test cases
    for (byte i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte n = byte.Parse(parts[0]); // Read n (number of boxes)
      byte k = byte.Parse(parts[1]); // Read k (maximum reversal length)
      parts = Console.ReadLine().Split();
      bool ans = true; // Assume we can sort the array
      
      // Special case when k == 1: only reversal of length 1 is allowed
      if (k == 1) {
        int[] a = new int[n]; // Create array to store box values
        for (byte j = 0; j < n; j++)
          a[j] = int.Parse(parts[j]); // Fill the array
        
        // Check if array is already sorted
        for (byte j = 1; j < n && ans; j++)
          ans = (a[j] >= a[j - 1]); // If any element is less than previous, it's not sorted
      }
      // For k > 1, we can sort any array, so default answer is YES
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/