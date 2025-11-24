// Problem: CF 1607 H - Banquet Preparations 2
// https://codeforces.com/contest/1607/problem/H

﻿/*
 * Problem: H. Banquet Preparations 2
 * 
 * Purpose: 
 *   This code minimizes the variety of dishes by determining how much fish and meat
 *   the taster should consume from each dish such that the number of distinct
 *   (fish, meat) combinations after consumption is minimized.
 * 
 * Algorithm:
 *   1. For each dish, compute a derived value p = a[i] + b[i] - m[i]
 *   2. Group dishes by this derived value
 *   3. For each group, sort dishes by their 'l' and 'r' values (derived from a[i] and b[i])
 *   4. Greedily assign values to minimize the number of distinct pairs
 * 
 * Time Complexity: O(n log n) per test case due to sorting operations
 * Space Complexity: O(n) for storing arrays and dictionaries
 */

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Banquet_Preparations_2 {
internal class Program {
  private static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  private static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
  private static void Main(string[] args) {
    int t = Next();
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }
  private static void Solve() {
    int n = Next();
    var a = new int[n];
    var aa = new int[n];  // Final amount of fish to eat from each dish
    var b = new int[n];
    var m = new int[n];
    for (int i = 0; i < n; i++) {
      a[i] = Next();
      b[i] = Next();
      m[i] = Next();
    }
    var d = new Dictionary<int, List<int>>();  // Group dishes by derived value p
    for (int i = 0; i < n; i++) {
      int p = a[i] + b[i] - m[i];
      List<int> list;
      if (!d.TryGetValue(p, out list)) {
        list = new List<int>();
        d[p] = list;
      }
      list.Add(i);
    }
    var l = new int[n];  // Lower bound for fish to eat from each dish
    var r = new int[n];  // Upper bound for fish to eat from each dish
    for (int i = 0; i < n; i++) {
      l[i] = Math.Max(0, a[i] - m[i]);     // Minimum fish that can be eaten (0 if negative)
      r[i] = a[i] - Math.Max(0, m[i] - b[i]);  // Maximum fish that can be eaten (a[i] - max(0, m[i]-b[i]))
    }
    int count = 0;  // Number of distinct (fish, meat) combinations after eating
    var f = new bool[n];  // Track which dishes have been processed
    foreach (var list in d.Values) {
      int[] li = list.ToArray();  // Dishes in this group, sorted by 'l'
      int[] ri = list.ToArray();  // Dishes in this group, sorted by 'r'
      Array.Sort(li, new Sort(l));  // Sort by lower bounds
      Array.Sort(ri, new Sort(r));  // Sort by upper bounds
      int j = 0;
      foreach (int i in ri) {
        if (f[i])
          continue;
        count++;  // Found a new distinct type
        aa[i] = r[i];  // Assign all possible fish from this dish
        f[i] = true;
        while (j < li.Length) {
          if (f[li[j]]) {
            j++;
            continue;
          }
          if (l[li[j]] <= r[i]) {  // If current lower bound is less than or equal to r[i]
            aa[li[j]] = r[i];  // Assign r[i] fish from dish li[j]
            f[li[j]] = true;
            j++;
          } else
            break;
        }
      }
    }
    writer.WriteLine(count);
    for (int i = 0; i < n; i++) {
      writer.Write(a[i] - aa[i]);  // Output fish eaten from dish i
      writer.Write(' ');
      writer.WriteLine(m[i] - (a[i] - aa[i]));  // Output meat eaten from dish i
    }
  }
  private static int Next() {
    int c;
    int res = 0;
    do {
      c = reader.Read();
      if (c == -1)
        return res;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return res;
      res *= 10;
      res += c - '0';
    }
  }
#region Nested type : Sort
  private class Sort : IComparer<int> {
    private readonly int[] _m;
    public Sort(int[] m) { _m = m; }
#region IComparer < int> Members
    public int Compare(int x, int y) { return _m[x].CompareTo(_m[y]); }
#endregion
  }
#endregion
}
}


// https://github.com/VaHiX/CodeForces/