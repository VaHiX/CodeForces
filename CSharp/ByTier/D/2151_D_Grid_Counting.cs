// Problem: CF 2151 D - Grid Counting
// https://codeforces.com/contest/2151/problem/D

/* 
 * Problem: D. Grid Counting
 * 
 * Purpose:
 *   Count the number of ways to color cells in an n x n grid such that:
 *   1. Each row k has exactly a[k] black cells.
 *   2. There is exactly one black cell in each row with max(x_i, y_i) = k.
 *   3. There is exactly one black cell in each row with max(x_i, n+1-y_i) = k.
 * 
 * Approach:
 *   - This problem involves combinatorics and dynamic programming on a tree-like structure.
 *   - The constraints define that for each row k:
 *     - There are exactly a[k] black cells.
 *     - There is one special cell in this row such that max(x_i, y_i) = k.
 *     - There is also exactly one special cell such that max(x_i, n+1-y_i) = k.
 *   - These two special rows form a structure akin to a Catalan number variant, where
 *     we can model the arrangement of valid pairs using combinations.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

﻿using System.Text;
using System.IO;
using System;
class Program {
  static long Solve() {
    int n = Next();
    int[] a = new int[n];
    long s = 0;
    for (int i = 0; i < n; i++)
      s += a[i] = Next(); // Read the array and compute sum
    if (s != n)
      return 0; // If total black cells is not equal to n, invalid configuration
    long ans = 1;
    for (int i = (n + 1) / 2; i < n; i++)
      if (a[i] > 0)
        return 0; // Check that rows from middle onwards have no black cells
    for (int i = (n + 1) / 2 - 1, c = 1 + (n + 1) % 2; i >= 0; i--, c += 2) {
      if (a[i] > c)
        return 0; // Check if number of black cells exceeds allowed maximum
      ans = ans * GetCFact(c, a[i]) % mod; // Compute combination C(c, a[i])
      c -= a[i]; // Decrement the available slots
    }
    return ans;
  }
  private const int mod = 998244353;
  private static long[] fact;
  private static long[] fact1;
  private static void InitFact(int n) {
    fact = new long[n];
    fact1 = new long[n];
    fact[0] = 1;
    for (int i = 1; i < fact.Length; i++) {
      fact[i] = (fact[i - 1] * i) % mod; // Precompute factorials
    }
    fact1[n - 1] = Pow(fact[n - 1], mod - 2);
    for (int i = fact1.Length - 2; i >= 0; i--) {
      fact1[i] = (fact1[i + 1] * (i + 1)) % mod; // Precompute inverse factorials
    }
  }
  private static long GetCFact(int n, int k) {
    return (((fact[n] * fact1[k]) % mod) * fact1[n - k]) % mod; // Combination C(n, k)
  }
  private static long Pow(long a, int k) {
    long r = 1;
    while (k > 0) {
      if ((k & 1) == 1) {
        r = (r * a) % mod;
      }
      a = (a * a) % mod;
      k >>= 1;
    }
    return r;
  }
  static void Main(string[] args) {
    InitFact(200001); // Initialize factorial arrays up to 200001
    long t = Next();
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve());
    writer.Flush();
  }
  static int Next() {
    int c;
    int m = 1;
    int res = 0;
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
  static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/CodeForces/