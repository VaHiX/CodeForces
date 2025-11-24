// Problem: CF 1748 D - ConstructOR 
// https://codeforces.com/contest/1748/problem/D

/* 
 * Problem: ConstructOR
 * Purpose: Given integers a, b, and d, find an integer x in the range [0, 2^60) such that both (a | x) and (b | x) are divisible by d.
 * Algorithm: 
 *   - If both a and b are divisible by d, then x = 0 is a valid solution.
 *   - Otherwise, we compute c = a | b. If c is divisible by d, then x = c is valid.
 *   - If not, we attempt to find a suitable x by solving a modular equation.
 *   - The core idea uses Extended Euclidean Algorithm to find modular inverse for solving the equation.
 * 
 * Time Complexity: O(t * log(min(a, b, d))) where t is number of test cases.
 * Space Complexity: O(1) - constant extra space used, excluding input and output storage.
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static long x, y;
  static long gcdExtended(long a, long b) {
    if (a == 0) {
      x = 0;
      y = 1;
      return b;
    }
    long gcd = gcdExtended(b % a, a);
    long x1 = x;
    long y1 = y;
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
  }
  static long modInverse(long A, long M) {
    long res = -1;
    long g = gcdExtended(A, M);
    if (g == 1)
      res = (x % M + M) % M;
    return res;
  }
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a0 =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = -1;
      long a = a0[0];
      long b = a0[1];
      long d = a0[2];
      if (a % d == 0 && b % d == 0) {
        o = 0;
      } else {
        long c = a | b;
        if (c % d == 0)
          o = c;
        else {
          long e = d - c % d;
          long g = gcdExtended(1024 * 1024 * 1024, d);
          if (e % g == 0) {
            long f = modInverse(1024 * 1024 * 1024 / g, d / g);
            if (f > 0)
              o = ((f * e / g) % (d / g)) * 1024 * 1024 * 1024 + c;
          }
        }
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/