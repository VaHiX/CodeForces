// Problem: CF 1699 D - Almost Triple Deletions
// https://codeforces.com/contest/1699/problem/D

﻿/*
 * Problem: D. Almost Triple Deletions
 * 
 * Algorithm/Techniques:
 * - Dynamic Programming with segment DP
 * - Preprocessing to find deletable segments
 * - Finding maximum length of equal elements possible after operations
 * 
 * Time Complexity:
 *   - Preprocessing deletable segments: O(n^2)
 *   - DP computation: O(n^2)
 *   - Overall: O(n^2) per test case
 * 
 * Space Complexity:
 *   - O(n^2) for the deletable boolean matrix
 *   - O(n) for the dp array and other auxiliary structures
 *   - Overall: O(n^2)
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = long.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      long o = 0;
      bool[,] deletable = new bool[n, n];
      for (int i = 0; i < n; i++) {
        Dictionary<int, int> u = new Dictionary<int, int>(); // Count of each element in current segment
        int currentMaxCount = 0; // Maximum count of any element in current segment
        for (int j = i; j < n; j++) {
          if (!u.ContainsKey(a[j]))
            u.Add(a[j], 1);
          else
            u[a[j]]++;
          var q = u[a[j]];
          if (q > currentMaxCount) {
            currentMaxCount = q; // Update max count
          }
          // If segment has even length and total elements >= 2 * max count, we can delete
          if ((j - i + 1) % 2 == 0 && (j - i + 1) >= 2 * currentMaxCount)
            deletable[i, j] = true;
        }
      }
      int[] dp = new int[n + 1]; // dp[i] represents max equal elements for prefix ending at i
      dp[0] = 1;
      for (int i = 1; i < n; i++) {
        if (deletable[0, i - 1]) // If entire prefix can be deleted
          dp[i] = 1;
        for (int j = 0; j < i; j++) {
          // If elements at i and j are same and middle segment can be deleted
          if (a[i] == a[j] && (deletable[j + 1, i - 1] || i - j == 1)) {
            if (dp[j] > 0 || deletable[0, j - 1])
              dp[i] = Math.Max(dp[i], dp[j] + 1);
          }
        }
      }
      var r = a.Distinct().ToList(); // Unique elements in array
      for (int i = 0; i < r.Count; i++) {
        for (int j = 0; j < n; j++) {
          // Look for valid segments ending at some position that can have a final equal element
          if (r[i] == a[j] && (n - j == 1 || deletable[j + 1, n - 1])) {
            if (dp[j] > 0 || deletable[0, j - 1])
              o = Math.Max(o, dp[j]);
          }
        }
      }
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/