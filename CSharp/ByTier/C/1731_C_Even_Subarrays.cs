// Problem: CF 1731 C - Even Subarrays
// https://codeforces.com/contest/1731/problem/C

﻿/*
 * Problem: C. Even Subarrays
 * 
 * Purpose: Count the number of subarrays whose XOR has an even number of divisors.
 * 
 * Algorithm:
 * - Use a prefix XOR approach with a frequency array to efficiently count valid subarrays.
 * - For each prefix XOR value, check how many previous prefix XORs, when XORed with it, yield a perfect square (which have odd number of divisors).
 * - Subtract those from total subarrays to get those with even number of divisors.
 * 
 * Time Complexity: O(n * sqrt(max(a)) + n) where n is the array length and max(a) is the maximum element.
 * Space Complexity: O(n + sqrt(max(a))) for the frequency array and the list of perfect squares.
 * 
 * Techniques:
 * - Prefix XOR
 * - Perfect square detection
 * - Frequency counting
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
      List<int> h = new List<int>();
      // Compute the next power of 2 greater than sqrt(max(a)) + 1
      double k1 = Math.Sqrt(a.Max()) + 1;
      k1 = Math.Pow(2, Math.Ceiling(Math.Log(k1) / Math.Log(2))) + 2;
      // Generate all perfect squares up to the computed limit
      for (int i = 0; i < k1; i++)
        h.Add(i * i);
      
      int[] d = new int[800000];
      int c = 0;
      a.Insert(0, 0); // Insert 0 at the start to make prefix XOR easier to handle
      int hv = h.Count;
      var h1 = h.ToArray();
      
      for (int i = 0; i <= n; i++) {
        c ^= a[i]; // Compute prefix XOR up to index i
        
        // Check how many previous prefix XOR values can be XORed with current prefix XOR to result in a perfect square
        for (int j = 0; j < hv; j++) {
          int v = c ^ h1[j];
          o += d[v];
        }
        
        d[c]++; // Increment the frequency of the current prefix XOR value
      }
      
      // Subtract subarrays with odd number of divisors from total subarrays
      o *= -1;
      o += (n + n * n) / 2;
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/