// Problem: CF 2035 D - Yet Another Real Number Problem
// https://codeforces.com/contest/2035/problem/D

/*
 * Problem: D. Yet Another Real Number Problem
 * 
 * Algorithm: Greedy with Stack-like Approach
 * 
 * Time Complexity: O(n * log(max_value)) where n is the length of array and max_value is the maximum element
 * Space Complexity: O(n * log(max_value)) due to storing powers of 2 and the val list
 * 
 * Approach:
 * - For each number in the array, we decompose it into odd part and power of 2
 * - We maintain a stack of (odd_part, power_of_2) pairs
 * - When processing a new number, we try to merge it with the top of the stack if possible
 * - We use a greedy approach to always keep the largest possible values at the top
 * - We compute the total sum modulo 10^9 + 7
 */

using System;
using System.Collections.Generic;
class Program {
  // Helper function to compare two numbers in compressed form
  // Compares (x, y) with (odd_part, power) where actual value is odd_part * 2^power
  static bool Cmp(int x, int y, int z) {
    if (z > 30)
      return true;
    return x < y * (1L << z); // x < y * 2^z
  }
  static void Main(string[] args) {
    System.IO.Stream inputStream = Console.OpenStandardInput();
    System.IO.StreamReader reader = new System.IO.StreamReader(inputStream);
    string input = reader.ReadToEnd();
    string[] tokens = input.Split(new char[] { ' ', '\t', '\n', '\r' },
                                  StringSplitOptions.RemoveEmptyEntries);
    int index = 0;
    if (index >= tokens.Length)
      return;
    int t = int.Parse(tokens[index++]);
    while (t-- > 0) {
      if (index >= tokens.Length)
        break;
      int n = int.Parse(tokens[index++]);
      List<int> a = new List<int>(n);
      for (int i = 0; i < n; i++) {
        if (index >= tokens.Length) {
          break;
        }
        a.Add(int.Parse(tokens[index++]));
      }
      const int mod = 1000000007;
      // val stores pairs of (odd_part, power_of_2)
      List<(int, int)> val = new List<(int, int)>();
      long ans = 0;
      // Precompute powers of 2 modulo mod to avoid recomputation
      long[] pow2 = new long[n * 32 + 1];
      pow2[0] = 1;
      for (int i = 1; i <= n * 32; i++) {
        pow2[i] = (pow2[i - 1] * 2) % mod;
      }
      List<string> results = new List<string>();
      foreach (var num in a) {
        int x = num;
        int y = 0;
        // Decompose number into odd part and power of 2
        while (x % 2 == 0) {
          x /= 2;
          y++;
        }
        // Try to merge with existing elements in stack if beneficial
        while (val.Count > 0 && Cmp(val[val.Count - 1].Item1, x, y)) {
          // Remove the top element from sum (subtract it)
          ans = (ans -
                 (val[val.Count - 1].Item1 * pow2[val[val.Count - 1].Item2]) %
                     mod +
                 mod) %
                mod;
          // Add the odd part directly (since we're just removing power of 2)
          ans = (ans + val[val.Count - 1].Item1) % mod;
          // Increase the power of 2 for the new element
          y += val[val.Count - 1].Item2;
          // Remove the top element from list
          val.RemoveAt(val.Count - 1);
        }
        // Add the new element to the list
        val.Add((x, y));
        // Add the contribution of the new element to the sum
        ans =
            (ans + (val[val.Count - 1].Item1 * pow2[val[val.Count - 1].Item2]) %
                       mod) %
            mod;
        results.Add(ans.ToString());
      }
      Console.WriteLine(string.Join(" ", results));
    }
  }
}


// https://github.com/VaHiX/CodeForces/