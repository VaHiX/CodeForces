// Problem: CF 2091 E - Interesting Ratio
// https://codeforces.com/contest/2091/problem/E

/*
 * Problem: Count "Interesting Ratio" pairs (a, b) such that 1 <= a < b <= n and F(a,b) = lcm(a,b)/gcd(a,b) is prime.
 * 
 * Approach:
 * - Precompute all primes up to max(n) using Sieve of Eratosthenes.
 * - For each number n, iterate through primes p and count valid pairs (a,b) where F(a,b) = p.
 * - For a prime p and pair (a,b) with F(a,b) = p:
 *   - If a = 1, then b must be p.
 *   - If a > 1, then b = a * p, and we also consider higher powers.
 * 
 * Time Complexity: O(n log log n + n * sqrt(n)) — sieve + iterating pairs
 * Space Complexity: O(n) — for storing primes up to n
 */

using System;
using System.Collections.Generic;
using System.Linq;

public static class CompatibilityAnalyzer {
  public static long[] CountPrimeCompatibility(int[] n) {
    long[] results = new long[n.Length];
    int maxN = n.Max();
    List<int> primes = SieveOfEratosthenes(maxN); // Generate all primes up to maxN
    for (int i = 0; i < n.Length; ++i) {
      results[i] = CountPairs(n[i], primes); // Count valid pairs for each n
    }
    return results;
  }

  private static List<int> SieveOfEratosthenes(int limit) {
    bool[] isPrime = new bool[limit + 1];
    for (int i = 2; i <= limit; i++) {
      isPrime[i] = true; // Initially all numbers are assumed to be prime
    }
    for (int p = 2; p * p <= limit; p++) {
      if (isPrime[p]) {
        for (int i = p * p; i <= limit; i += p) // Mark multiples of p as non-prime
          isPrime[i] = false;
      }
    }
    List<int> primes = new List<int>();
    for (int p = 2; p <= limit; p++) {
      if (isPrime[p]) {
        primes.Add(p); // Collect the primes
      }
    }
    return primes;
  }

  private static long CountPairs(int n, List<int> primes) {
    long count = 0;
    foreach (int p in primes) {
      if (p > n)
        break; // Stop if prime exceeds n
      
      long pk = p;
      while (pk <= n) {
        count++; // Add pair (1, p) or higher powers
        if ((double)pk * p > n)
          break;
        pk *= p;
      }

      for (int a = 2; a <= n / p; ++a) { // Iterate over possible base 'a'
        if (a % p != 0) { // Only consider cases where a is not divisible by p
          long ap = (long)a * p; // Compute b = a * p
          if (ap <= n) {
            count++; // Add pair (a, a*p)
            long apk = ap * p;
            while (apk <= n) {
              count++; // Add powers of (a*p) that are <= n
              if ((double)apk * p > n)
                break;
              apk *= p;
            }
          }
        }
      }
    }
    return count;
  }
}

class Solution {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    int[] nValues = new int[t];
    for (int i = 0; i < t; i++) {
      nValues[i] = int.Parse(Console.ReadLine());
    }
    long[] results = CompatibilityAnalyzer.CountPrimeCompatibility(nValues);
    for (int i = 0; i < results.Length; i++) {
      Console.WriteLine(results[i]);
    }
  }
}


// https://github.com/VaHiX/codeForces/