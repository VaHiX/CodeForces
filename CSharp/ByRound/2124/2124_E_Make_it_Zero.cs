// Problem: CF 2124 E - Make it Zero
// https://codeforces.com/contest/2124/problem/E

/*
E. Make it Zero
Algorithm: Greedy + Prefix Sum
Time Complexity: O(n) per test case
Space Complexity: O(n) for the array storage

The problem allows performing operations on an array where we select a subarray b such that 
the prefix sum equals the suffix sum at some index i. Then subtract b from a to make elements zero.

Key idea:
- If 2 * max_element > total_sum, it's impossible (because no way to split).
- If total_sum is odd, also impossible.
- Otherwise, we can always find a valid split using prefix sums and adjust greedily.

Approach:
1. Check if it's possible (sum even and max element not more than half the sum).
2. Compute prefix sums until we find a valid midpoint (prefix sum = suffix sum).
3. If such point exists, construct two operations:
   - First operation: subtract b from a to make total sum equal (using a greedy approach).
   - Second operation: finish remaining adjustments.
*/

﻿using System.Text;
namespace MakeItZero;
class Program {
  static void Solve() {
    long n = Next();
    long[] a = new long[n];
    for (int i = 0; i < n; i++)
      a[i] = Next();
    long sum = a.Sum();
    long max = a.Max();
    if (2 * max > sum || sum % 2 == 1) {
      writer.WriteLine("-1");
      return;
    }
    long s = 0;
    for (int i = 0; i < n; i++) {
      s += a[i];
      if (s * 2 >= sum) { // Found a valid cut point
        long p = (s - (sum - s)) / 2; // Determine how much to subtract from current prefix
        if (p == 0) {
          writer.WriteLine("1");
          for (int j = 0; j < n; j++) {
            writer.Write(a[j]);
            writer.Write(' ');
          }
          writer.WriteLine();
        } else {
          long[] b = new long[n];
          b[i] = p; // Adjust the current index
          a[i] -= p;
          for (int j = i - 1; p > 0 && j >= 0; j--) { // Greedily adjust previous elements
            long q = Math.Min(p, a[j]);
            p -= q;
            b[j] = q;
            a[j] -= q;
          }
          writer.WriteLine("2");
          for (int j = 0; j < n; j++) {
            writer.Write(b[j]);
            writer.Write(' ');
          }
          writer.WriteLine();
          for (int j = 0; j < n; j++) {
            writer.Write(a[j]);
            writer.Write(' ');
          }
          writer.WriteLine();
        }
        return;
      }
    }
  }
  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      Solve();
    writer.Flush();
  }
  static long Next() {
    int c;
    int m = 1;
    long res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/