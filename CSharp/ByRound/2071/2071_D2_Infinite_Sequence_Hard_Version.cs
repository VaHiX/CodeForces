// Problem: CF 2071 D2 - Infinite Sequence (Hard Version)
// https://codeforces.com/contest/2071/problem/D2

/* 
 * Purpose: This code efficiently computes the sum of elements in a given range [l, r] 
 *          for an infinite binary sequence a, where a[m] is defined using prefix XOR of 
 *          previous terms up to floor(m/2). The solution uses memoization and precomputed 
 *          arrays to handle large ranges (up to 10^18) by recognizing repeating patterns.
 *
 * Algorithms/Techniques:
 * - Prefix XOR computation for generating sequence terms
 * - Memoization via preF and preH arrays to avoid recomputation
 * - Pattern recognition and mathematical summation to handle large ranges
 * - Efficient range sum queries using precomputed prefix sums
 *
 * Time Complexity: O(n^2 + T * log(T)) where T is the size of precomputed arrays
 * Space Complexity: O(n^2) for precomputed arrays
 */

using System;
using System.Collections.Generic;
public static class Program {
  public static long M0; // Size of precomputed arrays
  public static uint C_val; // Value representing pattern
  public static uint[] preF; // Prefix XOR array
  public static long[] preH; // Prefix sum array of preF

  // Gets the value of a[m] using precomputed values or recursive logic
  public static uint getF(long m) {
    if (m <= M0) {
      return preF[(int)m];
    }
    if ((m & 1L) == 1L) {
      return C_val;
    }
    return (uint)(C_val ^ getF(m / 2)); // XOR pattern
  }

  // Gets prefix sum up to index x using recursive logic
  public static long getH(long x) {
    if (x <= M0) {
      return preH[(int)x];
    }
    long baseVal = preH[(int)M0];
    long L = M0 + 1;
    long R = x;
    long num = R - L + 1;
    long odd_count, even_count;
    if ((L % 2) == 1) {
      odd_count = (num + 1) / 2;
      even_count = num / 2;
    } else {
      even_count = (num + 1) / 2;
      odd_count = num / 2;
    }
    long L_even = (L + 1) / 2;
    long R_even = R / 2;
    long even_sum = 0;
    if (L_even <= R_even) {
      long hR = getH(R_even);
      long hLminus = (L_even > 1 ? getH(L_even - 1) : 0);
      even_sum = hR - hLminus;
    }
    long contrib_even = 0;
    if (C_val == 0) {
      contrib_even = even_sum;
    } else {
      contrib_even = even_count - even_sum;
    }
    long sum_part = odd_count * C_val + contrib_even;
    return baseVal + sum_part;
  }

  // Calculates sum of F values from M to N
  public static long F_sum(long M, long N) {
    long k_low_even = (M + 1) / 2;
    long k_high_even = N / 2;
    long sum_even = 0;
    if (k_low_even <= k_high_even) {
      long hR = getH(k_high_even);
      long hLminus = (k_low_even > 1 ? getH(k_low_even - 1) : 0);
      sum_even = hR - hLminus;
    }
    long k_low_odd;
    if ((M % 2) == 1) {
      k_low_odd = (M - 1) / 2;
    } else {
      k_low_odd = M / 2;
    }
    long k_high_odd = (N - 1) / 2;
    long sum_odd = 0;
    if (k_low_odd <= k_high_odd) {
      long hR = getH(k_high_odd);
      long hLminus = (k_low_odd > 0 ? getH(k_low_odd - 1) : 0);
      sum_odd = hR - hLminus;
    }
    return sum_even + sum_odd;
  }

  // Returns sum up to x using precomputed prefix sums
  public static long getS(long x, int n, long[] givenS, uint[] a) {
    if (x <= n) {
      return givenS[(int)x];
    }
    long part1 = givenS[n];
    long part2 = F_sum(n + 1, x);
    return part1 + part2;
  }

  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine() ?? "0");
    while (t-- > 0) {
      string[] tokens = (Console.ReadLine() ?? "").Split();
      int n = int.Parse(tokens[0]);
      long l = long.Parse(tokens[1]);
      long r = long.Parse(tokens[2]);
      uint[] a = new uint[n + 1];
      string[] arrLine = (Console.ReadLine() ?? "").Split();
      for (int i = 1; i <= n; i++) {
        int bit = int.Parse(arrLine[i - 1]);
        a[i] = (uint)bit;
      }
      long[] givenS = new long[n + 1];
      givenS[0] = 0;
      for (int i = 1; i <= n; i++) {
        givenS[i] = givenS[i - 1] + a[i];
      }
      if (r <= n) {
        long ansSimple = givenS[(int)r] - (l > 1 ? givenS[(int)(l - 1)] : 0);
        Console.WriteLine(ansSimple);
        continue;
      }
      long T_val = (n % 2 == 0) ? (n + 1) : (n + 2);
      M0 = Math.Max(2L * n, T_val);
      preF = new uint[M0 + 1];
      preH = new long[M0 + 1];
      preF[1] = a[1];
      for (int i = 2; i <= n; i++) {
        preF[i] = (uint)(preF[i - 1] ^ a[i]); // Prefix XOR
      }
      for (long i = n + 1; i <= M0; i++) {
        uint ai = preF[(int)(i / 2)];
        preF[i] = (uint)(preF[i - 1] ^ ai); // Recursive formula
      }
      preH[1] = preF[1];
      for (long i = 2; i <= M0; i++) {
        preH[i] = preH[i - 1] + preF[i]; // Prefix sum of F
      }
      C_val = preF[(int)T_val]; // Pattern value
      long S_r = getS(r, n, givenS, a);
      long S_l_1 = (l > 1 ? getS(l - 1, n, givenS, a) : 0);
      long ans = S_r - S_l_1;
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/