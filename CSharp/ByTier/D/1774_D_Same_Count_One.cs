// Problem: CF 1774 D - Same Count One
// https://codeforces.com/contest/1774/problem/D

// Problem: Make all arrays have the same count of 1s using minimum swaps
// Algorithm:
// 1. Calculate total number of 1s and check if it's divisible by n (if not, impossible)
// 2. For each position (column) independently:
//    - Identify arrays that have more 1s than average (lmax) and those with fewer (lmin)
//    - For each excess 1 in lmax, find a deficit 0 in lmin (same position)
//    - Swap them and record the operation
// Time Complexity: O(n * m) - Each element is processed once per column
// Space Complexity: O(n * m) - Storage for input arrays and intermediate lists
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;
class Solution {
  public static void Main(string[] args) {
    int t1 = Convert.ToInt32(Console.ReadLine());
    for (int a1 = 1; a1 <= t1; a1++) {
      int[] nrb = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
      int n = nrb[0];
      int m = nrb[1];
      var lll = new List<int[]>();
      for (int qr = 0; qr < n; qr++) {
        int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        lll.Add(arr);
      }
      long ss = 0;
      var ssl = new List<long>();
      foreach (int[] ar in lll) {
        long s1 = 0;
        foreach (int x in ar)
          s1 += x;
        ssl.Add(s1);
        ss += s1;
      }
      if (ss % lll.Count != 0) {
        Console.WriteLine(-1);
        continue;
      }
      long dd = ss / lll.Count();
      var res = new List<string>();
      for (int x = 0; x < lll[0].Length; x++) {
        var lmin = new List<int>(); // indices of arrays with less 1s than average
        var lmax = new List<int>(); // indices of arrays with more 1s than average
        for (int y = 0; y < lll.Count; y++) {
          if (ssl[y] > dd && lll[y][x] == 1)
            lmax.Add(y);
          if (ssl[y] < dd && lll[y][x] == 0)
            lmin.Add(y);
        }
        while (lmax.Count > 0 && lmin.Count > 0) {
          res.Add((lmax.First() + 1) + " " + (lmin.First() + 1) + " " +
                  (x + 1));
          ssl[lmax.First()]--;
          ssl[lmin.First()]++;
          lmax.RemoveAt(0);
          lmin.RemoveAt(0);
        }
      }
      Console.WriteLine(res.Count);
      foreach (string x in res)
        Console.WriteLine(x);
    }
  }
}


// https://github.com/VaHiX/CodeForces/