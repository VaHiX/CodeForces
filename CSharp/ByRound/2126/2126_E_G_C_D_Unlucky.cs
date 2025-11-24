// Problem: CF 2126 E - G-C-D, Unlucky!
// https://codeforces.com/contest/2126/problem/E

/*
E. G-C-D, Unlucky!
Time Complexity: O(n * log(min(p[i], s[i]))) per test case
Space Complexity: O(n) per test case

Algorithms/Techniques:
- Prefix and suffix GCD validation
- GCD computation using Euclidean algorithm
- Validation checks on divisibility and GCD properties

The solution verifies if there exists an array such that the given prefix GCD array 'p' and suffix GCD array 's' are consistent with each other.
*/

using System;
using System.Collections.Generic;
using System.Linq;
public class Program {
  static long GCD(long a, long b) {
    while (b != 0) {
      long temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      long[] p = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
      long[] s = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
      long g = p[n - 1]; // Last element of prefix GCD array is the GCD of entire array
      bool ok = true;
      if (s[0] != g) // First element of suffix GCD should also be the overall GCD
        ok = false;
      for (int i = 1; i < n && ok; i++)
        if (p[i - 1] % p[i] != 0) // Each prefix GCD must be divisible by the next one
          ok = false;
      for (int i = 0; i < n - 1 && ok; i++)
        if (s[i + 1] % s[i] != 0) // Each suffix GCD must be divisible by the previous one
          ok = false;
      for (int i = 0; i < n && ok; i++)
        if (GCD(p[i], s[i]) != g) // The GCD of corresponding elements in p and s should equal overall GCD
          ok = false;
      for (int i = 0; i < n - 1 && ok; i++)
        if (GCD(p[i], s[i + 1]) != g) // Check GCD consistency between adjacent elements
          ok = false;
      Console.WriteLine(ok ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/