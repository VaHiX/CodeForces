// Problem: CF 1759 D - Make It Round
// https://codeforces.com/contest/1759/problem/D

﻿/*
Algorithm: Find the roundest number of the form n*k where 1 <= k <= m
Approach:
1. Factor n into prime factors 2 and 5 to determine how many trailing zeros it already has
2. Try to increase the number of trailing zeros by multiplying by 2s and 5s up to m
3. If we can't make it more rounded, return n*m

Time Complexity: O(log n + log m) per test case, as we factor n and then perform a few divisions
Space Complexity: O(1) - only using a constant amount of extra space

Techniques:
- Prime factorization
- Greedy approach to maximize trailing zeros
- Integer arithmetic with overflow handling
*/

using System;
using System.Collections.Generic;
using System.Linq;
namespace ConsoleApp1 {
enum job { MEMBER, MENTOR, ADMIN }
class Program {
  static void Main(string[] args) {
    List<ulong> output = new List<ulong>();
    ulong tt = ulong.Parse(Console.ReadLine());
    while (tt != 0) {
      ulong n = 0, m = 0;
      string[] s = Console.ReadLine().Split(' ');
      n = ulong.Parse(s[0]);
      m = ulong.Parse(s[1]);
      ulong cnt2 = 0, cnt5 = 0;
      ulong k = 1;
      ulong n0 = n;
      // Factor out all 2s from n
      while (n > 0 && n % 2 == 0) {
        n /= 2;
        cnt2 += 1;
      }
      // Factor out all 5s from n
      while (n > 0 && n % 5 == 0) {
        n /= 5;
        cnt5 += 1;
      }
      // Try to balance 2s and 5s by multiplying by 2s if needed
      while (cnt2 < cnt5 && k * 2 <= m) {
        cnt2 += 1;
        k *= 2;
      }
      // Try to balance 2s and 5s by multiplying by 5s if needed
      while (cnt5 < cnt2 && k * 5 <= m) {
        cnt5 += 1;
        k *= 5;
      }
      // Try to multiply by 10s as long as possible
      while (k * 10 <= m) {
        k *= 10;
      }
      // If no multiplication was done, return n*m
      if (k == 1) {
        output.Add(n0 * m);
      } else {
        // Multiply by the maximum possible k that keeps the number within limits
        k *= m / k;
        output.Add(n0 * k);
      }
      tt--;
    }
    foreach (var item in output) {
      Console.WriteLine(item);
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/