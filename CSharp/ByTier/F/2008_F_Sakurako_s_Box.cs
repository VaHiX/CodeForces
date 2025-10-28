// Problem: CF 2008 F - Sakurako's Box
// https://codeforces.com/contest/2008/problem/F

/*
F. Sakurako's Box

Purpose:
This program calculates the expected value of the product of two randomly selected elements from an array,
and returns the result in the form P * Q^(-1) mod (10^9 + 7).

Algorithm:
- For each test case, compute the expected value of the product of two distinct elements.
- The expected value is calculated using the formula:
    E = ( sum of a[i] * a[j] for all i < j ) / C(n, 2)
- To efficiently calculate this, precompute suffix sums and use modular arithmetic.
- Finally multiply by modular inverses to get the result in required form.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the array 'b' used for suffix sums

The key steps involve:
1. Precomputing suffix sums (b[i] = sum of a[i] to a[n-1])
2. Calculating partial products and summing them up
3. Using modular inverse for division in modular arithmetic
*/

using System.Numerics;
using System;

public class hello {
  public static int MOD = 1000000007;
  
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      getAns(n, a);
    }
  }
  
  // Modular multiplicative inverse using Fermat's little theorem
  static int ModInv(int a, int m) => (int)BigInteger.ModPow(a, m - 2, m);
  
  static void getAns(int n, long[] a) {
    var b = new long[n];
    b[n - 1] = a[n - 1]; // Initialize last element of suffix sum array
    
    // Compute suffix sums: b[i] = a[i] + a[i+1] + ... + a[n-1]
    for (int i = n - 2; i >= 0; i--) {
      b[i] = b[i + 1] + a[i];
      b[i] %= MOD;
    }
    
    var ans = 0L;
    
    // Calculate contribution of each element to the total sum of products
    for (int i = 0; i < n - 1; i++) {
      var w = a[i] * b[i + 1]; // Multiply current element with suffix sum
      w %= MOD;
      ans += w;
      ans %= MOD;
    }
    
    // Double the result because we consider unordered pairs (i,j) and (j,i)
    ans *= 2;
    ans %= MOD;
    
    // Divide by C(n, 2) = n*(n-1)/2 using modular inverse
    ans *= ModInv(n, MOD);     // Multiply by 1/n mod MOD
    ans %= MOD;
    ans *= ModInv(n - 1, MOD); // Multiply by 1/(n-1) mod MOD
    ans %= MOD;
    
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/