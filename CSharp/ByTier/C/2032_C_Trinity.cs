// Problem: CF 2032 C - Trinity
// https://codeforces.com/contest/2032/problem/C

/*
Algorithm: Binary Search on Answer + Sliding Window
Purpose: To find the minimum number of operations to make all triplets of distinct indices form non-degenerate triangles.
Time Complexity: O(n log n), where n is the size of the array due to sorting and binary search.
Space Complexity: O(1), only using a few extra variables.
*/

using System;
using System.Linq;
public class Program {
  public static void Solve(long[] a, int n) {
    // Sort the array to facilitate checking triangle inequality efficiently
    Array.Sort(a);
    int ans = n; // Initialize answer to maximum possible operations (all elements changed)
    int left = 1, right = n; // Binary search range: minimum to maximum possible group sizes
    
    while (left <= right) {
      int mid = left + (right - left) / 2; // Midpoint of binary search range
      bool found = false; // Flag to check if valid group of size 'mid' exists
      
      if (mid == 1) {
        // If group size is 1, we need to change all elements except one
        ans = Math.Min(ans, n - 1);
        left = mid + 1;
        continue;
      }
      
      // Check for valid group of 'mid' elements
      for (int i = 0; i + mid - 1 < n; i++) {
        // Sum of two smallest elements in the group
        long sum = a[i] + a[i + 1];
        // If this sum is greater than largest element, valid triangle condition holds
        if (sum > a[i + mid - 1]) {
          found = true;
          break;
        }
      }
      
      if (found) {
        // If valid group found, we can reduce number of operations
        ans = Math.Min(ans, n - mid);
        left = mid + 1; // Try to find a larger valid group
      } else {
        right = mid - 1; // No valid group; try smaller group size
      }
    }
    Console.WriteLine(ans);
  }
  public static void Main() {
    var tokens = Console.ReadLine()
                     .Split(new char[] { ' ', '\n', '\r' },
                            StringSplitOptions.RemoveEmptyEntries)
                     .ToList();
    int ptr = 0;
    int tests = int.Parse(tokens[ptr++]);
    for (int t = 0; t < tests; t++) {
      if (ptr >= tokens.Count)
        tokens.AddRange(
            Console.ReadLine().Split(new char[] { ' ', '\n', '\r' },
                                     StringSplitOptions.RemoveEmptyEntries));
      int n = int.Parse(tokens[ptr++]);
      long[] a = new long[n];
      for (int i = 0; i < n; i++) {
        if (ptr >= tokens.Count)
          tokens.AddRange(
              Console.ReadLine().Split(new char[] { ' ', '\n', '\r' },
                                       StringSplitOptions.RemoveEmptyEntries));
        a[i] = long.Parse(tokens[ptr++]);
      }
      Solve(a, n);
    }
  }
}


// https://github.com/VaHiX/CodeForces/