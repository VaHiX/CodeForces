// Problem: CF 2033 F - Kosuke's Sloth
// https://codeforces.com/contest/2033/problem/F

/*
 * Problem: Kosuke's Sloth - Find the n-th Fibonacci number divisible by k
 * 
 * Algorithm:
 * - Preprocess all values of k up to 10^5 to compute periods and positions of Fibonacci numbers divisible by k
 * - Use the periodic property of Fibonacci numbers modulo k to find the n-th occurrence efficiently
 * - Time Complexity: O(k^2) for preprocessing (since Fibonacci sequence mod k is periodic with period at most 6k)
 * - Space Complexity: O(k^2) due to storing positions and periods for each k
 * 
 * The key idea is that Fibonacci numbers modulo k repeat after a certain period.
 * We track all indices where Fibonacci numbers are divisible by k and use modular arithmetic
 * to calculate the n-th such index without computing all preceding Fibonacci numbers.
 */

using System;
using System.Collections.Generic;
class Program {
  const long MOD = 1000000007;
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    var testCases = new List<(long n, long k)>();
    var uniqueKSet = new HashSet<long>();
    for (int i = 0; i < t; i++) {
      var inputs = Console.ReadLine().Split();
      long n = long.Parse(inputs[0]);
      long k = long.Parse(inputs[1]);
      testCases.Add((n, k));
      uniqueKSet.Add(k);
    }
    var uniqueKs = new List<long>(uniqueKSet);
    const long MAX_K = 100000;
    long[] periods = new long[MAX_K + 1]; // Stores the period of Fibonacci mod k
    long[] counts = new long[MAX_K + 1]; // Counts how many times 0 appears in each period
    var positions = new List<long>[MAX_K + 1]; // Stores positions of 0 in Fibonacci mod k
    for (int i = 0; i <= MAX_K; i++)
      positions[i] = new List<long>();
    foreach (long k in uniqueKs) {
      if (k == 1)
        continue;
      long fPrev = 1 % k;
      long fCurr = 1 % k;
      long pos = 2;
      long maxIterations = 6 * k + 10;
      bool periodFound = false;
      for (long iter = 0; iter < maxIterations; iter++) {
        long fNext = (fPrev + fCurr) % k;
        pos++;
        if (fNext == 0) {
          positions[(int)k].Add(pos); // Record the position where Fibonacci number is divisible by k
        }
        fPrev = fCurr;
        fCurr = fNext;
        if (fPrev == 1 && fCurr == 1) {
          periods[(int)k] = pos - 2; // Period starts from the next step, so subtract 2
          counts[(int)k] = positions[(int)k].Count;
          periodFound = true;
          break;
        }
      }
      if (!periodFound) {
        periods[(int)k] = pos - 2;
        counts[(int)k] = positions[(int)k].Count;
      }
    }
    foreach (var testCase in testCases) {
      long n = testCase.n;
      long k = testCase.k;
      long y;
      long q = (k == 1) ? 0 : (n - 1) / counts[(int)k]; // Quotient to find full periods
      long r = (k == 1) ? 0 : (n - 1) % counts[(int)k]; // Remainder to find position in last period
      if (k == 1) {
        y = n % MOD;
      } else {
        y = ((q % MOD) * (periods[(int)k] % MOD) % MOD +
             (positions[(int)k][(int)r] % MOD)) %
            MOD;
      }
      Console.WriteLine(y);
    }
  }
}


// https://github.com/VaHiX/CodeForces/