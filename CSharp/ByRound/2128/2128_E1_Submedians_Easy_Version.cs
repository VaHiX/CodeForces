// Problem: CF 2128 E1 - Submedians (Easy Version)
// https://codeforces.com/contest/2128/problem/E1

/*
 * Problem: E1. Submedians (Easy Version)
 * 
 * Purpose: Given an array of integers and a minimum subarray length k,
 * find the maximum possible median value among all valid subarrays of length at least k.
 * 
 * Algorithm:
 * - Binary search on the answer (median value).
 * - For each candidate median, check if there exists a valid subarray where
 *   this value can be a median.
 * - To check, we convert the problem into a prefix sum comparison:
 *   - We treat elements >= threshold as +1, others as -1.
 *   - Then look for a subarray of length at least k with non-negative prefix sum.
 * 
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 */

using System;
using System.Collections.Generic;
class Program {
  struct Segment {
    public int Left;
    public int Right;
  }
  
  // Check if there exists a subarray of length at least k with median >= threshold
  static bool IsPossible(List<int> a, int k, int threshold,
                         out Segment segment) {
    int n = a.Count;
    var prefix = new int[n + 1]; // Prefix sum array for transformed values
    segment = new Segment { Left = -1, Right = -1 };
    
    // Build prefix sums: +1 if element >= threshold, -1 otherwise
    for (int i = 1; i <= n; i++) {
      prefix[i] = prefix[i - 1] + (a[i - 1] >= threshold ? 1 : -1);
    }
    
    int minPrefix = 0;
    int minPosition = 0;

    // Iterate over all possible subarrays of length k
    for (int i = k; i <= n; i++) {
      // Maintain minimum prefix sum in the window [i-k, i-1]
      if (prefix[i - k] < minPrefix) {
        minPrefix = prefix[i - k];
        minPosition = i - k;
      }
      
      // If current prefix - minPrefix >= 0, it means we found a valid subarray
      if (prefix[i] - minPrefix >= 0) {
        segment.Left = minPosition + 1;
        segment.Right = i;
        return true;
      }
    }
    return false;
  }
  
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var tokens = Console.ReadLine().Split();
      int n = int.Parse(tokens[0]);
      int k = int.Parse(tokens[1]);
      
      var elements = Console.ReadLine().Split();
      var a = new List<int>(n);
      foreach (var num in elements)
        a.Add(int.Parse(num));
        
      int low = 1, high = n, answer = 1;
      Segment finalSegment = new Segment();
      
      // Binary search on the maximum possible median
      while (low <= high) {
        int mid = (low + high) / 2;
        if (IsPossible(a, k, mid, out _)) {
          answer = mid;
          low = mid + 1; // Try to find a higher median
        } else {
          high = mid - 1; // Lower the threshold
        }
      }
      
      // Retrieve actual segment with maximum median found
      IsPossible(a, k, answer, out finalSegment);
      Console.WriteLine($"{answer} {finalSegment.Left} {finalSegment.Right}");
    }
  }
}


// https://github.com/VaHiX/CodeForces/