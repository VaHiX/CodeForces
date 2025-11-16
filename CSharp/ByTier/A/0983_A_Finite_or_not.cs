// Problem: CF 983 A - Finite or not?
// https://codeforces.com/contest/983/problem/A

using System;
class Program {
  // Purpose: Determine if the fraction p/q in base b has a finite representation.
  // Algorithm: The fraction p/q in base b is finite if and only if all prime factors
  //            of the reduced denominator (q/gcd(p,q)) are also prime factors of b.
  //            This is done by repeatedly dividing the denominator by the GCD of
  //            the denominator and base until the denominator becomes 1.
  // Time Complexity: O(log(q) + log(b)) per query, due to GCD operations.
  // Space Complexity: O(1), only using a constant amount of extra space.

  static long gcd(long a, long b) {
    if (b == 0) {
      return a;
    }
    return gcd(b, a % b);
  }
  static void Main(string[] args) {
    int T = int.Parse(Console.ReadLine());
    while (T-- > 0) {
      long p, q, b;
      string[] input = Console.ReadLine().Split();
      p = long.Parse(input[0]);
      q = long.Parse(input[1]);
      b = long.Parse(input[2]);
      // Reduce the fraction to its simplest form by removing common factors
      q /= gcd(p, q);
      // Keep dividing the denominator by the GCD of denominator and base
      // until the denominator becomes 1 or no more division is possible
      while (b != 1) {
        b = gcd(q, b);
        q /= b;
      }
      // If the denominator is reduced to 1, then all prime factors of the
      // original denominator are also prime factors of the base -> finite
      if (q == 1) {
        Console.WriteLine("Finite");
      } else {
        Console.WriteLine("Infinite");
      }
    }
  }
}

// https://github.com/VaHiX/CodeForces/