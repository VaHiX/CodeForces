// Problem: CF 1090 M - The Pleasant Walk
// https://codeforces.com/contest/1090/problem/M

﻿/*
 * Problem: M. The Pleasant Walk
 * 
 * Algorithm: Sliding Window / Two Pointers
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * Approach:
 * - We iterate through the array and maintain a current count of consecutive houses with different colors.
 * - When we encounter a house with the same color as the previous one, we reset the current count to 1.
 * - We keep track of the maximum count seen so far.
 * 
 * Example:
 * Input: [1, 2, 3, 3, 2, 1, 2, 2]
 * Output: 4 (segment from index 3 to 6: [3, 2, 1, 2])
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Globalization;
using System.Threading;
namespace M {
class Program {
  static void Main(string[] args) {
    Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;
    int tc = 1;
    while (tc-- > 0) {
      solve();
    }
  }
  static void solve() {
    int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    int n = arr[0];
    int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    int cur = 1;           // Current length of valid segment ending at index i
    int maximal = 1;       // Maximum length found so far
    for (int i = 1; i < n; i++) {
      if (a[i] != a[i - 1]) {
        cur++;             // Extend the current segment if colors differ
      } else {
        cur = 1;           // Reset the segment length if colors are the same
      }
      maximal = Math.Max(cur, maximal);  // Update maximum length
    }
    Console.WriteLine(maximal);
  }
}
}


// https://github.com/VaHiX/CodeForces/