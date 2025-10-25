// Problem: CF 2104 D - Array and GCD
// https://codeforces.com/contest/2104/problem/D

/*
 * Problem: D. Array and GCD
 * Purpose: Given an array of integers, determine the minimum number of elements to remove
 *          so that the remaining array can be transformed into an ideal array.
 *          An ideal array satisfies:
 *            1. All elements are at least 2.
 *            2. For all pairs of distinct indices, GCD of their values is 1.
 * 
 * Algorithms:
 *   - Sieve of Eratosthenes for generating primes up to a large enough limit
 *   - Prefix sums to compute cumulative sums efficiently
 *   - Greedy approach with sorting in descending order to maximize the number of elements that can be kept
 * 
 * Time Complexity: O(L log log L + m^2) where L is the upper bound for primes (about 17m + 100),
 *                  and m is the maximum size of input arrays in a test case.
 * Space Complexity: O(L + m) where L is the sieve size and m is the maximum number of elements
 */

using System;
using System.Collections.Generic;
using System.Linq;

class Program {
  static List<long> Sieve(int m) {
    int L = m * 17 + 100; // Upper bound for primes needed, ensures safety margin
    bool[] isPrime = new bool[L + 1];
    for (int i = 0; i <= L; i++) {
      isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not primes
    
    // Sieve of Eratosthenes
    for (int i = 2; i * i <= L; i++) {
      if (isPrime[i]) {
        for (int j = i * i; j <= L; j += i) {
          isPrime[j] = false;
        }
      }
    }
    
    List<long> primes = new List<long>();
    for (int i = 2; i <= L; i++) {
      if (isPrime[i]) {
        primes.Add(i);
        if (primes.Count == m)
          break; // Early exit once we have enough primes
      }
    }
    
    // Construct prefix sum array S where S[i] represents sum of first i primes
    List<long> S = new List<long>(new long[m + 1]);
    for (int i = 1; i <= m; i++) {
      S[i] = S[i - 1] + primes[i - 1];
    }
    return S;
  }
  
  static List<List<int>> ReadInput(out int m) {
    int t = int.Parse(Console.ReadLine());
    List<List<int>> tests = new List<List<int>>(t);
    m = 0;
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split(' ');
      List<int> test = new List<int>(n);
      for (int j = 0; j < n; j++) {
        test.Add(int.Parse(parts[j]));
      }
      tests.Add(test);
      if (n > m)
        m = n;
    }
    return tests;
  }
  
  static void Solve() {
    int m;
    List<List<int>> tests = ReadInput(out m);
    List<long> S = Sieve(m);
    
    foreach (var a in tests) {
      int n = a.Count;
      a.Sort((x, y) => y.CompareTo(x)); // Sort array in descending order for greedy selection
      
      long[] ps = new long[n + 1];
      for (int i = 0; i < n; i++) {
        ps[i + 1] = ps[i] + a[i]; // Compute prefix sums of sorted array
      }
      
      int best = 0;
      for (int i = 1; i <= n; i++) {
        if (ps[i] >= S[i]) {
          best = i; // Find largest i such that sum of top i elements is at least sum of first i primes
        }
      }
      Console.WriteLine(n - best); // Minimum removals = total elements minus best kept ones
    }
  }
  
  static void Main() { Solve(); }
}


// https://github.com/VaHiX/CodeForces/