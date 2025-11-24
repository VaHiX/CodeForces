// Problem: CF 1341 A - Nastya and Rice
// https://codeforces.com/contest/1341/problem/A

﻿/*
 * Problem: Nastya and Rice
 * Purpose: Determine if the given constraints on individual grain weights and total package weight are consistent.
 * 
 * Algorithm:
 * - For each test case, calculate the minimum and maximum possible total weights based on individual grain constraints.
 * - Check if the feasible range of total weights [min, max] overlaps with the given range [c - d, c + d].
 * - If there's an overlap, then it's possible to assign weights to grains such that the total weight falls in the required range.
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each case is processed in constant time.
 * Space Complexity: O(1), only a constant amount of extra space is used.
 */
using System;
using System.IO;
using System.Text;
namespace Nastya_and_Rice {
internal class Program {
  private static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  private static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
  private static void Main(string[] args) {
    int t = Next();
    for (int i = 0; i < t; i++) {
      writer.WriteLine(Solve() ? "Yes" : "No");
    }
    writer.Flush();
  }
  private static bool Solve() {
    int n = Next(); // Number of grains
    int a = Next(); // Mean weight of grains
    int b = Next(); // Deviation from mean weight
    int c = Next(); // Mean weight of total package
    int d = Next(); // Deviation from mean package weight
    
    // Calculate minimum possible total weight (all grains at minimum weight)
    int min = n * (a - b);
    // Calculate maximum possible total weight (all grains at maximum weight)
    int max = n * (a + b);
    
    // If the minimum possible total is greater than the maximum allowed total, impossible
    if (min > c + d)
      return false;
    // If the maximum possible total is less than the minimum allowed total, impossible
    if (max < c - d)
      return false;
    // If both conditions above are false, there is overlap and solution is possible
    return true;
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
}
}


// https://github.com/VaHiX/CodeForces/