// Problem: CF 1624 E - Masha-forgetful
// https://codeforces.com/contest/1624/problem/E

/*
 * Problem: Masha-forgetful
 * Purpose: Given a list of known phone numbers and a new phone number,
 *          split the new number into segments that match substrings from
 *          the known numbers, where each segment has length at least 2.
 * 
 * Algorithm: Dynamic Programming with preprocessing
 * 1. Preprocess all known phone numbers to find all 2-digit and 3-digit 
 *    substrings and their positions in which phone number they come from.
 * 2. Use dynamic programming to find if the target number can be split.
 * 3. Reconstruct the solution by backtracking through DP table.
 * 
 * Time Complexity: O(n * m^2 + m^2) where n is number of known phones, m is length of phones
 * Space Complexity: O(n * m + m) for storing phone numbers and DP table
 */

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Masha_forgetful {
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
    int m = Next();
    var nm = new int[n + 1, m]; // Store all n+1 phone numbers (0 to n-1 are known, n is target)
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        nm[i, j] = Next(true);
      }
    }
    // d2[i] stores (phone_index, start_pos) for 2-digit number i
    var d2 = new Tuple<int, int>[100];
    // d3[i] stores (phone_index, start_pos) for 3-digit number i  
    var d3 = new Tuple<int, int>[1000];
    // Precompute all possible 2-digit and 3-digit substrings from known numbers
    for (int nn = 0; nn < n; nn++) {
      for (int j = 0; j + 1 < m; j++) {
        int h = 0;
        for (int i = 0; i < 3 && i + j < m; i++) {
          h = h * 10 + nm[nn, i + j];
          if (i == 1 && d2[h] == null) // If 2-digit num and not yet found
            d2[h] = new Tuple<int, int>(nn, j);
          if (i == 2 && d3[h] == null) // If 3-digit num and not yet found
            d3[h] = new Tuple<int, int>(nn, j);
        }
      }
    }
    // dp[i] = (phone_index, start_pos, length) of the last segment ending at position i-1
    var dp = new Tuple<int, int, int>[m + 1];
    dp[0] = new Tuple<int, int, int>(-1, 0, 0); // Base case, 0 digits processed
    
    // Fill DP table
    for (int ii = 0; ii < m; ii++) {
      if (dp[ii] != null) {
        int h = 0;
        for (int i = 0; i < 3 && i + ii < m; i++) {
          h = h * 10 + nm[n, i + ii]; // h represents the number from the current test string
          if (i == 1 && d2[h] != null && dp[ii + 2] == null) // Found 2-digit match and not already marked
            dp[ii + 2] = new Tuple<int, int, int>(d2[h].Item1, d2[h].Item2, 2);
          if (i == 2 && d3[h] != null && dp[ii + 3] == null) // Found 3-digit match and not already marked
            dp[ii + 3] = new Tuple<int, int, int>(d3[h].Item1, d3[h].Item2, 3);
        }
      }
    }
    
    // If we couldn't make a full division, output -1
    if (dp[m] == null)
      writer.WriteLine("-1");
    else {
      // Reconstruct path from DP table
      var s = new Stack<Tuple<int, int, int>>();
      int i = m;
      while (i > 0) {
        s.Push(dp[i]);
        i = i - dp[i].Item3; // Backtrack to previous segment
      }
      writer.WriteLine(s.Count);
      foreach (var t in s) {
        writer.Write(t.Item2 + 1); // Convert to 1-indexed start position
        writer.Write(' ');
        writer.Write(t.Item2 + t.Item3); // End position (1-indexed)
        writer.Write(' ');
        writer.WriteLine(t.Item1 + 1); // Convert to 1-indexed phone number
      }
    }
  }
  private static int Next(bool one = false) {
    int c;
    int res = 0;
    do {
      c = reader.Read();
      if (c == -1)
        return res;
    } while (c < '0' || c > '9');
    res = c - '0';
    if (one)
      return res;
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return res;
      res *= 10;
      res += c - '0';
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/