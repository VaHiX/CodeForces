// Problem: CF 1725 H - Hot Black Hot White
// https://codeforces.com/contest/1725/problem/H

﻿/*
 * Problem: H. Hot Black Hot White
 * 
 * Purpose: 
 *   This solution determines how to color N magical stones (N is even) into black (0) or white (1) 
 *   such that exactly N/2 stones are black and N/2 are white. It also selects a magic coefficient Z 
 *   (0, 1, or 2) to ensure no two stones react with each other. Stones react if their concatenated 
 *   values satisfy a modular arithmetic condition with Z.
 *   
 * Algorithm:
 *   - Classify stones by A[i] % 3:
 *     - Count stones where A[i] % 3 == 0 (let c = count)
 *   - Case 1: If c <= N/2:
 *     - Color all stones with A[i] % 3 == 0 as white (1)
 *     - Color remaining stones as black (0) until N/2 blacks are used
 *     - Set Z = 0
 *   - Case 2: If c > N/2:
 *     - Color all stones with A[i] % 3 != 0 as white (1)
 *     - Color remaining stones as black (0) until N/2 blacks are used
 *     - Set Z = 2
 *   
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < fyt; z++) {
      var n = int.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToArray();
      long o = 0;
      var c = a.Where(i => i % 3 == 0).Count(); // Count stones with strength divisible by 3
      
      if (c <= n / 2) {
        // If less than or equal to half, use Z = 0
        output.Add("0");
        StringBuilder sb = new StringBuilder();
        int t = 0; // Counter for black stones used
        for (int i = 0; i < n; i++) {
          if (t == n / 2 || a[i] % 3 == 0) {
            // Use white (1) if we've used all blacks or current stone is divisible by 3
            sb.Append("1");
          } else {
            // Otherwise use black (0)
            sb.Append("0");
            t++;
          }
        }
        output.Add(sb.ToString());
      } else {
        // If more than half, use Z = 2
        output.Add("2");
        StringBuilder sb = new StringBuilder();
        int t = 0; // Counter for black stones used
        for (int i = 0; i < n; i++) {
          if (t == n / 2 || a[i] % 3 != 0) {
            // Use white (1) if we've used all blacks or current stone is NOT divisible by 3
            sb.Append("1");
          } else {
            // Otherwise use black (0)
            sb.Append("0");
            t++;
          }
        }
        output.Add(sb.ToString());
      }
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/