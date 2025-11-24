// Problem: CF 2065 C2 - Skibidus and Fanum Tax (hard version)
// https://codeforces.com/contest/2065/problem/C2

/*
 * Problem: C2. Skibidus and Fanum Tax (hard version)
 * Algorithm: Greedy with Binary Search (LowerBound)
 * Time Complexity: O(n * log(m) + m * log(m)) per test case
 * Space Complexity: O(1) additional space (excluding input arrays)
 *
 * Description:
 * Given two arrays 'a' and 'b', we can modify elements of array 'a' by choosing
 * an element from 'b' such that a[i] = b[j] - a[i]. The goal is to determine if
 * it's possible to sort 'a' in non-decreasing order using these operations.
 *
 * Approach:
 * - Sort array 'b' once to enable binary search queries.
 * - Use a greedy strategy to construct a valid sequence where each element of 'a'
 *   can be updated to a value that helps maintain the increasing order.
 * - For each element in 'a', we try to find the best possible value from 'b'
 *   such that the resulting value maintains or increases the cumulative minimum.
 * - A lower bound (binary search) is performed on sorted array 'b' to efficiently
 *   locate suitable candidates.
 */

using System.Collections.Generic;
using static System.Math;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      line = Console.ReadLine().Trim().Split(' ');
      var b = Array.ConvertAll(line, int.Parse);
      getAns(n, m, a, b);
    }
  }

  static void getAns(int n, int m, int[] a, int[] b) {
    Array.Sort(b); // Sort 'b' once for binary search
    var pre = Min(a[0], b[0] - a[0]); // Initialize with first element's potential value
    
    for (int i = 1; i < n; i++) {
      var p = LowerBound(b, pre + a[i]); // Find lower bound in sorted 'b'
      
      if (p == m) {
        // No valid element in 'b' to use
        if (a[i] >= pre)
          pre = a[i];  // Stick with current value
        else {
          Console.WriteLine("NO"); // Can't maintain ordering
          return;
        }
      } else {
        // Use the smallest available b[j] that allows valid transformation
        if (a[i] >= pre)
          pre = Min(b[p] - a[i], a[i]); // Choose minimal update
        else
          pre = b[p] - a[i]; // Update based on current value
      }
    }
    Console.WriteLine("YES");
  }

  static int LowerBound<T>(T[] arr, int start, int end, T value,
                           IComparer<T> comparer) {
    var low = start;
    var high = end;
    while (low < high) {
      var mid = (high + low) / 2;
      if (comparer.Compare(arr[mid], value) < 0)
        low = mid + 1;
      else
        high = mid;
    }
    return low;
  }

  static int LowerBound<T>(T[] arr, T value)
      where T : IComparable => LowerBound(arr,
                0,
                arr.Length,
                value,
                Comparer<T>.Default);
}


// https://github.com/VaHiX/codeForces/