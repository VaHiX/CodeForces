// Problem: CF 1999 F - Expected Median
// https://codeforces.com/contest/1999/problem/F

/*
F. Expected Median
Algorithm: Combinatorics + Preprocessing Factorials
Time Complexity: O(maxN + t * k) where maxN = 200000 and t is number of test cases
Space Complexity: O(maxN)

Approach:
- For each test case, we count how many 1s are in the array.
- Since k is odd, for a subsequence of length k to have median 1, at least (k+1)/2 elements must be 1.
- We iterate over all valid numbers of 1s (from (k+1)/2 to min(onesCount, k)) and sum up combinations:
    C(onesCount, i) * C(n - onesCount, k - i)
- Precompute factorials and inverse factorials for efficient combination calculation.
*/

using System;
using System.Collections.Generic;
class Program {
  const int MOD = 1000000007;
  static long[] fact;   // Stores factorials modulo MOD
  static long[] invFact; // Stores inverse factorials modulo MOD
  static void Main() {
    int maxN = 200000;
    PrecomputeFactorials(maxN);  // Precompute factorials and their inverses
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      var nk = Console.ReadLine().Split();
      int n = int.Parse(nk[0]);
      int k = int.Parse(nk[1]);
      var a = Console.ReadLine().Split();
      int[] arr = Array.ConvertAll(a, int.Parse);
      Console.WriteLine(SolveTestCase(n, k, arr));
    }
  }
  static void PrecomputeFactorials(int maxN) {
    fact = new long[maxN + 1];
    invFact = new long[maxN + 1];
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++) {
      fact[i] = fact[i - 1] * i % MOD;  // Compute factorials
    }
    invFact[maxN] = ModInverse(fact[maxN], MOD);  // Inverse of last factorial
    for (int i = maxN - 1; i >= 0; i--) {
      invFact[i] = invFact[i + 1] * (i + 1) % MOD;  // Precompute inverse factorials
    }
  }
  static long ModInverse(long a, long mod) { return Power(a, mod - 2, mod); }
  static long Power(long x, long y, long mod) {
    long result = 1;
    x = x % mod;
    while (y > 0) {
      if (y % 2 == 1) {
        result = (result * x) % mod;
      }
      y = y >> 1;
      x = (x * x) % mod;
    }
    return result;
  }
  static long Comb(int n, int k) {
    if (n < k || k < 0)
      return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;  // Calculate combination using precomputed factorials
  }
  static long SolveTestCase(int n, int k, int[] arr) {
    int onesCount = 0;
    foreach (int num in arr) {
      if (num == 1) {
        onesCount++;
      }
    }
    long result = 0;
    int halfK = (k + 1) / 2;  // Minimum number of 1s needed for median to be 1
    for (int i = halfK; i <= Math.Min(onesCount, k); i++) {
      result =
          (result + Comb(onesCount, i) * Comb(n - onesCount, k - i) % MOD) %
          MOD;
    }
    return result;
  }
}


// https://github.com/VaHiX/codeForces/