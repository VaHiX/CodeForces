// Problem: CF 2149 B - Unconventional Pairs
// https://codeforces.com/contest/2149/problem/B

/*
Problem: Unconventional Pairs
Purpose: Given an array of even length, pair elements to minimize the maximum difference between pairs.
Algorithm: 
    - Sort the array.
    - Pair adjacent elements (i, i+1) for i = 0, 2, 4, ..., n-2.
    - The maximum difference among these pairs is the answer.
Time Complexity: O(n log n) due to sorting; O(n) for pairing.
Space Complexity: O(1) excluding input storage.
*/

using System;
using System.Collections.Generic;
using System.IO;
class Solution {
  static void Main(String[] args) {
    int T = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int t = 0; t < T; t++) {
      int N = int.Parse(Console.ReadLine()); // Read size of array
      int[] A = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Read array elements
      Array.Sort(A); // Sort the array to facilitate optimal pairing
      int ans = 0;
      for (int i = 0; i < N; i = i + 2) {
        // Pair adjacent elements and compute max difference
        ans = Math.Max(ans, Math.Abs(A[i] - A[i + 1]));
      }
      Console.WriteLine(ans); // Output result for current test case
    }
  }
}


// https://github.com/VaHiX/CodeForces/