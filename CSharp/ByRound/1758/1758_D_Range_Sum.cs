// Problem: CF 1758 D - Range = √Sum
// https://codeforces.com/contest/1758/problem/D

﻿/*
 * Problem: D. Range = √Sum
 * 
 * Algorithm/Technique: Constructive Algorithm
 * 
 * Time Complexity: O(n) per test case, as we perform a constant number of operations
 *                    for each element in the sequence.
 * Space Complexity: O(n) for storing the sequence and intermediate results.
 * 
 * Approach:
 * 1. Start by generating a sequence of n distinct integers centered around a value.
 * 2. Adjust the sum to match the required condition where range (max - min) = sqrt(sum).
 * 3. Iterate and adjust the values to satisfy the equation while keeping them distinct.
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
      List<long> o = new List<long>();
      long s = 0;
      long st = (n + 1) * (n + 1); // Target sum = (n+1)^2, such that sqrt(sum) = n+1
      long k = n / 2;
      for (int i = 0; i < n; i++) {
        long t = k + 2 + i; // Generate initial sequence
        s += t;
        o.Add(t);
      }
      int round = 0;
      // Adjust values to make sum equal to target
      while (st > s) {
        for (long i = n - 1; i > 0; i--) {
          long ds = st - s;
          if (ds >= 2) {
            o[(int)i] += 2; // Increment by 2 to reduce difference
            s += 2;
          } else if (ds >= 1) {
            o[(int)i] += 1; // Increment by 1
            s++;
          } else
            break;
        }
        if (st > s) {
          o[0]++;
          s++; // Increment first element to avoid going below target
        }
        round++;
      }
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/