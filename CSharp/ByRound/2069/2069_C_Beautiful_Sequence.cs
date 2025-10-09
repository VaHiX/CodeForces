// Problem: CF 2069 C - Beautiful Sequence
// https://codeforces.com/contest/2069/problem/C

/*
C. Beautiful Sequence
Problem: Count the number of beautiful subsequences in an array where each element is 1, 2, or 3.
A beautiful subsequence must:
1. Have length at least 3
2. For every element except first, there's a smaller element to its left
3. For every element except last, there's a larger element to its right

Algorithm:
Uses dynamic programming with prefix counting and modular arithmetic:
- Process elements from left to right
- Track how many '1's seen so far (countOnes), sum of contributions from previous '1's (sumOnes)
- For each '2', increment count2 (number of 2s seen)
- For each '3', compute contribution using prefix sums and previously counted 1s/2s
- Use powers of 2 for efficient computation and modular inverse

Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(n) for precomputed powers of 2 and inverse powers of 2
*/

using System;
using System.Collections.Generic;
class Program {
  const int MOD = 998244353;
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    const int MAXP = 200005;
    long[] pow2 = new long[MAXP];
    long[] invPow2 = new long[MAXP];
    pow2[0] = 1;
    for (int i = 1; i < MAXP; i++) {
      pow2[i] = (pow2[i - 1] * 2) % MOD; // Precompute powers of 2
    }
    long inv2 = 499122177; // Modular inverse of 2 mod MOD
    invPow2[0] = 1;
    for (int i = 1; i < MAXP; i++) {
      invPow2[i] = (invPow2[i - 1] * inv2) % MOD; // Precompute inverse powers of 2
    }
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      long ans = 0;
      long sumOnes = 0;
      int countOnes = 0;
      int count2 = 0;
      for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
          // When encountering a '1', add its contribution to the running sum
          sumOnes = (sumOnes + invPow2[count2]) % MOD;
          countOnes++;
        } else if (a[i] == 2) {
          // When encountering a '2', just increment counter of 2s
          count2++;
        } else if (a[i] == 3) {
          // When encountering a '3', compute how many valid beautiful subsequences end here
          long contrib = ((pow2[count2] * sumOnes) % MOD - countOnes) % MOD;
          if (contrib < 0)
            contrib += MOD;
          ans = (ans + contrib) % MOD;
        }
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/