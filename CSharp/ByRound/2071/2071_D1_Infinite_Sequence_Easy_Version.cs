// Problem: CF 2071 D1 - Infinite Sequence (Easy Version)
// https://codeforces.com/contest/2071/problem/D1

/*
 * Problem: Infinite Sequence (Easy Version)
 * Purpose: Given a binary sequence defined by initial terms and a recursive rule for m > n,
 *          compute the sum of elements in range [l, r] where l == r.
 * 
 * Algorithm:
 * - For m <= n, directly return a[m]
 * - For m > n, use recursion based on the formula:
 *   a[m] = a[1] ^ a[2] ^ ... ^ a[ floor(m/2) ]
 * - Use prefix XORs and mathematical properties to avoid computing all values up to r.
 * 
 * Time Complexity: O(n) per test case due to processing of initial terms and recursion.
 * Space Complexity: O(n) for storing the array and prefix sums.
 */

using System;
using System.Collections.Generic;
using System.Linq;
class PerfectPermutation {
  // Recursive function to compute a[m] for m > n using prefix XOR and memoization
  static int F(long m, long n, int B, int[] p) {
    if (m <= n)
      return p[(int)m];  // Direct access to precomputed prefix XORs
    return (m % 2 == 1) ? B : B ^ F(m / 2, n, B, p);  // Use recurrence relation to calculate value
  }
  
  static void Solve() {
    string[] inputs = Console.ReadLine().Split();
    int n = int.Parse(inputs[0]);
    long l = long.Parse(inputs[1]);
    long r = long.Parse(inputs[2]);
    int[] a = new int[n + 1];
    inputs = Console.ReadLine().Split();
    for (int i = 1; i <= n; i++) {
      a[i] = int.Parse(inputs[i - 1]);
    }
    
    // If l is within the known range [1, n], output directly
    if (l <= n) {
      Console.WriteLine(a[(int)l]);
      return;
    }

    // Precompute prefix XORs p[i] = a[1] ^ a[2] ^ ... ^ a[i]
    int[] p = new int[n + 1];
    p[0] = 0;
    for (int i = 1; i <= n; i++) {
      p[i] = p[i - 1] ^ a[i];
    }

    // Calculate B based on parity of n and prefix XOR
    int fn = p[n];
    int B = (n % 2 == 1) ? fn : fn ^ p[n / 2];

    // Divide l by 2 to get m for recursive calculation
    long m = l / 2;
    Console.WriteLine(F(m, n, B, p));
  }
  
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0)
      Solve();
  }
}


// https://github.com/VaHiX/codeForces/