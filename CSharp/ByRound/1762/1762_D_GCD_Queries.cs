// Problem: CF 1762 D - GCD Queries 
// https://codeforces.com/contest/1762/problem/D

﻿/*
Purpose: 
This code solves the interactive problem "D. GCD Queries" where we need to find two indices x and y such that either p_x = 0 or p_y = 0 in a hidden permutation p of [0, 1, 2, ..., n-1]. 
The approach uses a divide-and-conquer strategy by comparing GCD values of pairs to identify elements that are likely to be 0.
Time Complexity: O(n log n)
Space Complexity: O(1)

Algorithm:
1. Initialize l = 1 and r = 2 as initial candidates.
2. For each query from 3 to n:
   - Query GCD(p_l, p_q) and GCD(p_r, p_q)
   - If GCD(p_l, p_q) > GCD(p_r, p_q), set r = q (update right candidate)
   - Else if GCD(p_l, p_q) < GCD(p_r, p_q), set l = q (update left candidate)
3. After identifying candidates l and r, output them as potential indices where p_l = 0 or p_r = 0.
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
      var n = int.Parse(Console.ReadLine());
      int l = 1;
      int r = 2;
      for (int q = 3; q <= n; q++) {
        // Query GCD of p_l and p_q
        Console.WriteLine("? " + (l).ToString() + " " + (q).ToString());
        long x = long.Parse(Console.ReadLine());
        // Query GCD of p_r and p_q
        Console.WriteLine("? " + (r).ToString() + " " + (q).ToString());
        long y = long.Parse(Console.ReadLine());
        // Update candidates based on GCD comparison
        if (x > y)
          r = q;
        else if (x < y)
          l = q;
      }
      // Output the final candidates
      Console.WriteLine("! " + (l).ToString() + " " + (r).ToString());
      Console.ReadLine();
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/