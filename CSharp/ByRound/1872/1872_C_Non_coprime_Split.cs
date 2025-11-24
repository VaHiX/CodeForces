// Problem: CF 1872 C - Non-coprime Split
// https://codeforces.com/contest/1872/problem/C

/*
 * Problem: Non-coprime Split
 * 
 * Algorithm:
 * - For a given range [l, r], find two positive integers a and b such that:
 *   1. l ≤ a + b ≤ r
 *   2. gcd(a, b) ≠ 1 (i.e., they are not coprime)
 * 
 * Approach:
 * - If r is even and r ≥ 4, we can split it as r/2 + r/2 (since gcd(r/2, r/2) = r/2 > 1).
 * - If r is odd and r ≥ 5 and r > l, we can split it as (r-1)/2 + (r-1)/2 (since gcd((r-1)/2, (r-1)/2) = (r-1)/2 > 1).
 * - If r == l and r is odd and composite, find its smallest prime factor p and set a = p, b = (r/p - 1) * p.
 * 
 * Time Complexity: O(√r) for each test case due to factorization (with precomputed primes).
 * Space Complexity: O(√r) for storing list of primes up to √r.
 */

using System;
using System.Collections.Generic;

public class NonCoprimeSplit {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    List<int> oddPrimes = new List<int>();
    oddPrimes.Add(3); // Initialize with first odd prime
    
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int l = int.Parse(parts[0]);
      int r = int.Parse(parts[1]);
      bool existSolution = false;
      int a = 0;
      int b = 0;
      
      // Case 1: r is even and r >= 4
      if (r >= 4 && r % 2 == 0) {
        existSolution = true;
        a = r / 2;
        b = a;
      }
      // Case 2: r is odd, r >= 5, and r > l
      else if (r >= 5 && r % 2 == 1 && r > l) {
        existSolution = true;
        a = (r - 1) / 2;
        b = a;
      }
      // Case 3: r == l and r is odd and composite
      else if (r >= 9 && r == l) {
        int minDivisor = MinDivisor(r, oddPrimes);
        if (minDivisor > 1) {
          existSolution = true;
          int d = r / minDivisor;
          a = minDivisor;
          b = (d - 1) * minDivisor;
        }
      }
      
      if (existSolution)
        Console.WriteLine("{0} {1}", a, b);
      else
        Console.WriteLine(-1);
    }
  }
  
  // Find the smallest prime divisor of n
  public static int MinDivisor(int n, List<int> p) {
    int limit = Convert.ToInt32(Math.Floor(Math.Sqrt(n)));
    int i = 0;
    int res = 1;
    
    // Check against known primes
    while (i < p.Count && p[i] <= limit && res == 1) {
      if (n % p[i] == 0)
        res = p[i];
      i++;
    }
    
    // Generate more primes up to limit if needed
    int pLast = p[p.Count - 1];
    while (pLast <= limit && res == 1) {
      pLast += 2;
      if (IsPrime(pLast, p)) {
        p.Add(pLast);
        if (n % pLast == 0)
          res = pLast;
      }
    }
    
    return res;
  }
  
  // Check if number n is prime using previously generated primes
  public static bool IsPrime(int n, List<int> p) {
    int limit = Convert.ToInt32(Math.Floor(Math.Sqrt(n)));
    int i = 0;
    bool res = true;
    
    while (i < p.Count && p[i] <= limit && res) {
      if (n % p[i] == 0)
        res = false;
      i++;
    }
    
    return res;
  }
}


// https://github.com/VaHiX/CodeForces/