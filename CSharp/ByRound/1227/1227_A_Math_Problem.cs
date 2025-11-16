// Problem: CF 1227 A - Math Problem
// https://codeforces.com/contest/1227/problem/A

﻿/*
 * Code Purpose: Find the minimum length of a segment that intersects all given segments on a 1D line.
 * 
 * Algorithm/Techniques: 
 * - The optimal segment must lie within the intersection of all given segments.
 * - To find this, we compute the maximum of all starting points (latestStart) and the minimum of all ending points (earliestEnd).
 * - The required segment is [latestStart, earliestEnd], and its length is max(0, latestStart - earliestEnd).
 * 
 * Time Complexity: O(n), where n is the number of segments. We iterate through all segments once.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
namespace Codeforces {
public class Program {
  public static int GetInt() => int.Parse(Console.ReadLine());
  public static long GetLong() => long.Parse(Console.ReadLine());
  public static int[] GetIntArray() =>
      Console.ReadLine().Trim().Split(' ').Select(int.Parse).ToArray();
  public static long[] GetLongArray() =>
      Console.ReadLine().Trim().Split(' ').Select(long.Parse).ToArray();
  public static double[] GetDoublesArray() =>
      Console.ReadLine()
          .Trim()
          .Split(' ')
          .Select(d => Convert.ToDouble(d, CultureInfo.InvariantCulture))
          .ToArray();
  public static string[] GetLines(int n) {
    var ans = new string[n];
    for (int i = 0; i < n; i++) {
      ans[i] = Console.ReadLine();
    }
    return ans;
  }
  public static long Gcd(long a, long b) => b == 0 ? a : Gcd(b, a % b);
  public static void Solve() {
    int n = GetInt();
    int latestStart = int.MinValue;   // Stores the maximum of all left endpoints
    int earliestEnd = int.MaxValue;   // Stores the minimum of all right endpoints
    for (int i = 0; i < n; i++) {
      var a = GetIntArray();
      latestStart = Math.Max(latestStart, a[0]);  // Update latest start point
      earliestEnd = Math.Min(earliestEnd, a[1]);  // Update earliest end point
    }
    int ans = Math.Max(0, latestStart - earliestEnd); // Length of the intersecting segment
    Console.WriteLine(ans);
  }
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++)
      Solve();
  }
}
}


// https://github.com/VaHiX/CodeForces/