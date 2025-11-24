// Problem: CF 2025 B - Binomial Coefficients, Kind Of
// https://codeforces.com/contest/2025/problem/B

/*
Problem: B. Binomial Coefficients, Kind Of
Algorithm: Precompute powers of 2 modulo 1e9+7
Time Complexity: O(100001 + n) where n is the number of test cases
Space Complexity: O(100001)

The task involves computing "wrong" binomial coefficients based on a flawed recurrence relation:
C[n][k] = C[n][k-1] + C[n-1][k-1] (incorrect)
Instead of the correct formula:
C[n][k] = C[n-1][k] + C[n-1][k-1]

However, by analyzing this incorrect recurrence, we notice that for fixed k and increasing n,
each step doubles the previous value. So C[n][k] = 2^(n-k) for k < n.

This is optimized using precomputed powers of 2 modulo 1e9+7.
*/

using System;
public class hello {
  public static int MOD = 1000000007;
  static void Main() {
    var n = int.Parse(Console.ReadLine().Trim());
    string[] line = Console.ReadLine().Trim().Split(' ');
    var a = Array.ConvertAll(line, int.Parse);
    line = Console.ReadLine().Trim().Split(' ');
    var b = Array.ConvertAll(line, int.Parse);
    getAns(n, a, b);
  }
  static void getAns(int n, int[] a, int[] b) {
    var t = new long[100001]; // Precompute powers of 2
    t[0] = 1;
    for (int i = 1; i < 100001; i++) {
      t[i] = t[i - 1] * 2;   // Double the previous value
      t[i] %= MOD;          // Keep modulo to prevent overflow
    }
    var ans = new long[n];
    for (int i = 0; i < n; i++)
      ans[i] = t[b[i]];     // For given n and k, answer is 2^(n-k)
    Console.WriteLine(string.Join("\n", ans));
  }
}


// https://github.com/VaHiX/codeForces/