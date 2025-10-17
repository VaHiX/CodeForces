// Problem: CF 2116 B - Gellyfish and Baby's Breath
// https://codeforces.com/contest/2116/problem/B

/*
 * Problem: B. Gellyfish and Baby's Breath
 * 
 * Purpose:
 *   Given two permutations p and q of [0, ..., n-1], compute an array r where each element
 *   r[i] = max_{j=0}^{i} (2^{p[j]} + 2^{q[i-j]}), modulo 998244353.
 * 
 * Approach:
 *   - Preprocess maximum indices for prefix maximums in both arrays p and q.
 *   - For each i, calculate the max value among all valid pairs (j, i-j).
 *   - Use fast exponentiation with modular arithmetic for powers of 2.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 */

using System.Numerics;
using System;

public class hello {
  public static int MOD = 998244353;
  
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var p = Array.ConvertAll(line, int.Parse);
      line = Console.ReadLine().Trim().Split(' ');
      var q = Array.ConvertAll(line, int.Parse);
      getAns(n, p, q);
    }
  }
  
  static void getAns(int n, int[] p, int[] q) {
    // Precompute prefix maximum indices for values in p and q
    var pmax = new int[n];
    var qmax = new int[n];
    pmax[0] = 0;
    qmax[0] = 0;
    
    // Build prefix max arrays
    for (int i = 1; i < n; i++) {
      pmax[i] = p[i] > p[pmax[i - 1]] ? i : pmax[i - 1];
      qmax[i] = q[i] > q[qmax[i - 1]] ? i : qmax[i - 1];
    }
    
    var ans = new long[n];
    
    // Initialize answer for first element
    var t = (int)BigInteger.ModPow(2, p[pmax[0]], MOD);
    var t2 = (int)BigInteger.ModPow(2, q[qmax[0]], MOD);
    ans[0] = t + t2;
    ans[0] %= MOD;
    
    // Process all elements from index 1 to n-1
    for (int i = 1; i < n; i++) {
      var av = p[pmax[i]];     // Max value in p up to current index
      var av2 = q[qmax[i]];    // Max value in q up to current index
      
      if (av > av2) {
        // Use p's max element at pmax[i] since it is larger than q's max
        var tt = (int)BigInteger.ModPow(2, p[pmax[i]], MOD);
        var tt2 = (int)BigInteger.ModPow(2, q[i - pmax[i]], MOD);
        ans[i] = (tt + tt2) % MOD;
      } else if (av < av2) {
        // Use q's max element at qmax[i] since it is larger than p's max
        var tt = (int)BigInteger.ModPow(2, q[qmax[i]], MOD);
        var tt2 = (int)BigInteger.ModPow(2, p[i - qmax[i]], MOD);
        ans[i] = (tt + tt2) % MOD;
      } else {
        // av == av2: use appropriate power based on comparison
        var aite = q[i - pmax[i]];
        var aite2 = p[i - qmax[i]];
        var tt = (int)BigInteger.ModPow(2, p[pmax[i]], MOD);
        int tt2;
        if (aite >= aite2)
          tt2 = (int)BigInteger.ModPow(2, q[i - pmax[i]], MOD);
        else
          tt2 = (int)BigInteger.ModPow(2, p[i - qmax[i]], MOD);
        ans[i] = (tt + tt2) % MOD;
      }
    }
    
    Console.WriteLine(string.Join(" ", ans));
  }
}


// https://github.com/VaHiX/CodeForces/