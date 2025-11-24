// Problem: CF 2033 D - Kousuke's Assignment
// https://codeforces.com/contest/2033/problem/D

/*
D. Kousuke's Assignment
Purpose: Calculate the maximum number of non-overlapping beautiful segments in an array.
A segment [l, r] is beautiful if the sum of elements from index l to r equals zero.
Algorithm: 
    - Use prefix sums and a SortedSet to track seen prefix sums.
    - When a prefix sum is repeated, it indicates a subarray with sum 0.
    - Reset tracking after each beautiful segment to ensure non-overlapping.
Time Complexity: O(n log n) due to operations on SortedSet (insert/delete).
Space Complexity: O(n) for storing prefix sums in the SortedSet.
*/

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public static class Solution {
  public static int MaxBeautifulSegments(int n, int[] a) {
    var seenSums = new SortedSet<long> { 0L }; // Initialize with 0 to handle segments starting from index 0
    long prefixSum = 0L; // Keeps track of cumulative sum up to current element
    int result = 0; // Count of beautiful segments found
    
    for (int i = 0; i < n; i++) {
      prefixSum += a[i]; // Add current element to prefix sum
      
      if (seenSums.Contains(prefixSum)) {
        // If we've seen this prefix sum before, the subarray between those indices sums to zero
        result++; // Increment the count of beautiful segments
        
        seenSums.Clear(); // Clear the set to start fresh for next non-overlapping segment
        prefixSum = 0L;   // Reset prefix sum for new segment
      }
      
      seenSums.Add(prefixSum); // Add current prefix sum to the set
    }
    
    return result;
  }
}

public class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split(
          new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
      int[] a = Array.ConvertAll(parts, int.Parse);
      int result = Solution.MaxBeautifulSegments(n, a);
      Console.WriteLine(result);
    }
  }
}


// https://github.com/VaHiX/codeForces/