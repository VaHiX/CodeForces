// Problem: CF 2005 B2 - The Strict Teacher (Hard Version)
// https://codeforces.com/contest/2005/problem/B2

/*
 * Problem: B2. The Strict Teacher (Hard Version)
 * Purpose: Given a 1D line of n cells with m teachers and q queries of David's position,
 *          determine the minimum number of moves required for teachers to catch David
 *          when both act optimally.
 *
 * Algorithms:
 * - For each query, find the closest teacher using binary search (LowerBound).
 * - If David is outside all teacher positions, distance is calculated as min of:
 *   - Distance from closest teacher to boundary (1 or n)
 * - If David is between two teachers, position is chosen to minimize
 *   max distance to either teacher (centered mid-point).
 *
 * Time Complexity: O(m * log m + q * log m) per test case.
 * Space Complexity: O(m + q)
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
      var q = int.Parse(line[2]);
      line = Console.ReadLine().Trim().Split(' ');
      var b = Array.ConvertAll(line, int.Parse); // teachers' positions
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse); // David's queries
      getAns(n, m, q, b, a);
    }
  }

  static void getAns(int n, int m, int q, int[] b, int[] a) {
    Array.Sort(b); // Sort teachers' positions for binary search
    var ans = new int[q];
    for (int i = 0; i < q; i++) {
      var p = LowerBound(b, a[i]); // Find the first position >= a[i]

      if (p == m) {
        // David is to the right of all teachers
        ans[i] = n - b[m - 1];
      }
      else if (p == 0) {
        // David is to the left of all teachers
        ans[i] = b[0] - 1;
      }
      else {
        // David is between two teachers
        var L = b[p - 1]; // Left teacher
        var r = b[p];     // Right teacher
        var t = (r - L) / 2 + L; // Midpoint of the segment
        ans[i] = Min(t - L, r - t); // Distance to closest boundary from center
      }
    }
    Console.WriteLine(string.Join("\n", ans));
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