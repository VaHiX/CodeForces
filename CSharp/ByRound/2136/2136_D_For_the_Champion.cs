// Problem: CF 2136 D - For the Champion
// https://codeforces.com/contest/2136/problem/D

﻿/*
D. For the Champion
Interactive problem to find initial coordinates (X, Y) of a robot on an infinite 2D plane given anchor points.

Algorithm:
Uses binary search and manhattan distance queries to deduce the initial position. 
Key idea is to compute maximums of (x_i + y_i) and (x_i - y_i) for all anchors.
Then uses strategic moves in four directions to probe the space efficiently,
calculating final coordinates from responses.

Time Complexity: O(n) per test case, where n is number of anchor points
Space Complexity: O(n) for storing anchor points

Approach:
1. Find max of (x_i + y_i) and max of (x_i - y_i) among all anchor points.
2. Use up/down/left/right queries to bound the search space.
3. Compute final coordinates x,y using derived formulas based on responses.

Key variables:
- max1: maximum of (x_i + y_i)
- max2: maximum of (x_i - y_i)
- The algorithm performs 9 queries to deduce bounds
*/
using System.Text;
namespace ForTheChampion;
class Program {
  static void Solve() {
    int n = int.Parse(reader.ReadLine());
    long max1 = long.MinValue;
    long max2 = long.MinValue;
    for (int i = 0; i < n; i++) {
      long[] pp = reader.ReadLine()
                      .Split(' ')
                      .Where(e => !string.IsNullOrEmpty(e))
                      .Select(long.Parse)
                      .ToArray();
      max1 = Math.Max(max1, pp[0] + pp[1]); // Track maximum of x+y
      max2 = Math.Max(max2, pp[0] - pp[1]); // Track maximum of x-y
    }
    long z = 1000000000;
    // Probe in directions to get necessary information
    Ask(0, z); // U
    Ask(0, z); // U  
    Ask(3, z); // R
    long p = Ask(3, z); // R - Store distance after right move
    Ask(1, z); // D
    Ask(1, z); // D
    Ask(1, z); // D
    Ask(1, z); // D
    Ask(1, z); // D
    long q = Ask(1, z); // D - Store distance after down move
    // Calculate final coordinates using derived formulas
    long x = (p + max1 + q + max2 - 10 * z) / 2;
    long y = p + max1 - x - 4 * z;
    Ans(x, y);
  }
  static long Ask(int dir, long k) {
    writer.Write("? ");
    switch (dir) {
    case 0:
      writer.Write("U "); // Up direction
      break;
    case 1:
      writer.Write("D "); // Down direction  
      break;
    case 2:
      writer.Write("L "); // Left direction
      break;
    case 3:
      writer.Write("R "); // Right direction
      break;
    }
    writer.WriteLine(k);
    writer.Flush();
    return long.Parse(reader.ReadLine());
  }
  static void Ans(long x, long y) {
    writer.WriteLine($"! {x} {y}");
    writer.Flush();
  }
  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/