// Problem: CF 1766 D - Lucky Chains
// https://codeforces.com/contest/1766/problem/D

﻿/*
 * Problem: D. Lucky Chains
 * 
 * Purpose:
 *   For each given pair (x, y), determine the length of the longest "lucky" chain starting from (x, y),
 *   where a chain is defined as (x, y), (x+1, y+1), ..., (x+k, y+k) and a chain is lucky if all pairs
 *   in it have gcd = 1. If the chain is infinitely long, return -1.
 * 
 * Approach:
 *   - A chain (x, y) -> (x+1, y+1) -> ... -> (x+k, y+k) can be lucky only if gcd(x+i, y+i) = 1 for all i.
 *   - Since gcd(x+i, y+i) = gcd((x+i) % d, (y+i) % d) for any d, we can analyze how gcd changes.
 *   - The key insight is that if d divides (y - x), then all pairs (x+i, y+i) will have a common factor d if and only if d also divides both (x+i) and (y+i).
 *   - Thus, if we factorize (y - x), for each prime factor d of (y - x), the longest valid chain is up to the smallest number of steps such that (x+i) % d == 0.
 *   - If (y - x) = 1, then the gcd will always be 1 and it's infinite — return -1.
 *   - Time complexity: O(n * sqrt(max_diff) + pi * sqrt(max_val)) where pi is the number of primes up to sqrt(max_val)
 *   - Space complexity: O(n + sqrt(max_val))
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static int GCD(int a, int b) {
    int Remainder;
    while (b != 0) {
      Remainder = a % b;
      a = b;
      b = Remainder;
    }
    return a;
  }
  public static Dictionary<int, int[]> divisors = new Dictionary<int, int[]>();
  public static List<int> FindDivisors(int n) {
    if (divisors.ContainsKey(n))
      return divisors[n].ToList();
    int no = n;
    List<int> d = new List<int>();
    for (int i = 0; i < primes.Count; i++) {
      if (n == 1)
        break;
      if (n % primes[i] == 0) {
        d.Add(primes[i]);
        n /= primes[i];
        while (n % primes[i] == 0)
          n /= primes[i];
      }
    }
    if (n > 1)
      d.Add(n);
    divisors.Add(no, d.Distinct().OrderBy(t => t).ToArray());
    return divisors[no].ToList();
  }
  static List<int> primes = new List<int>();
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    primes.Add(2);
    for (int i = 3; i < 3200; i++) {
      bool add = true;
      for (int j = 0; j < primes.Count; j++) {
        if (i % primes[j] == 0) {
          add = false;
          break;
        }
      }
      if (add)
        primes.Add(i);
    }
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
      long o = 0;
      if (a[1] - a[0] == 1)
        o = -1; // If the difference is 1, then the pair is already lucky, and we have infinite chain
      else {
        o = int.MaxValue;
        var d = FindDivisors(a[1] - a[0]);
        for (int i = 0; i < d.Count; i++) {
          // For each divisor d of (y - x), try to compute the minimum number of steps
          // until (x + i) is divisible by d
          o = Math.Min(o, (d[i] - (a[0] + d[i]) % d[i]) % d[i]);
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