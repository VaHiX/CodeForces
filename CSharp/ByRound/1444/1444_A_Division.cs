// Problem: CF 1444 A - Division
// https://codeforces.com/contest/1444/problem/A

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using static System.Math;

/// <summary>
/// Problem: Find the largest divisor x of p such that x is not divisible by q.
/// 
/// Algorithm:
/// - If p is not divisible by q, then p itself is the answer.
/// - Otherwise, factorize q into primes and for each prime factor key with count qcnt in q,
///   determine the minimum power of key that must be removed from p to ensure x is not divisible by q.
/// - Compute the minimal required divisor (mindiv) and return p / mindiv.
/// 
/// Time Complexity: O(sqrt(q) + log(p)) per test case
/// Space Complexity: O(log(q)) for storing prime factors of q
/// </summary>
public static class P {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
  }
  static void Solve() {
    var ab = Console.ReadLine().Split().Select(long.Parse).ToArray();
    var p = ab[0];
    var q = ab[1];
    if (p % q != 0) {
      Console.WriteLine(p);
      return;
    }
    long mindiv = long.MaxValue;
    foreach (var item in PrimeFactors(q).GroupBy(x => x)) {
      var key = item.Key;
      int pcnt = 0;
      long val = p;
      while (val % key == 0) {
        val /= key;
        pcnt++;
      }
      var qcnt = item.Count();
      long div = 1;
      for (int i = 0; i <= pcnt - qcnt; i++)
        div *= key;
      mindiv = Min(mindiv, div);
    }
    Console.WriteLine(p / mindiv);
  }
  static IEnumerable<long> PrimeFactors(long n) {
    while ((n & 1) == 0) {
      n >>= 1;
      yield return 2;
    }
    for (long i = 3; i * i <= n; i += 2) {
      while (n % i == 0) {
        n /= i;
        yield return i;
      }
    }
    if (n != 1)
      yield return n;
  }
}


// https://github.com/VaHiX/CodeForces/