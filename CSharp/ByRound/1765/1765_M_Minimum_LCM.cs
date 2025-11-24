// Problem: CF 1765 M - Minimum LCM
// https://codeforces.com/contest/1765/problem/M

// ***************************************************************
// Problem: M. Minimum LCM
// Algorithm: Find two positive integers a and b such that a + b = n and LCM(a, b) is minimized.
// Approach: 
//   - Try all divisors of n up to sqrt(n) to find candidate pairs (x, y) where x = n / j and y = n - x.
//   - For each such pair, compute LCM = (x * y) / GCD(x, y), but since we're interested in minimizing
//     LCM, we observe that LCM is minimized when |x - y| is minimized.
//   - The algorithm checks all divisors of n from 2 to sqrt(n), and for each valid divisor,
//     computes the corresponding pair (x, y) and keeps track of the one with minimum difference.
//   - If no such divisor is found (i.e., n is prime), the pair (1, n-1) is returned.
// Time Complexity: O(sqrt(n)) per test case
// Space Complexity: O(1) (excluding output storage)
// ***************************************************************

using System;
using System.Text;
public class MinimumLcm {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    byte t = byte.Parse(Console.ReadLine());
    for (byte i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      short bound = Convert.ToInt16(Math.Floor(Math.Sqrt(n)) + 1);
      int a = 0;
      int b = 0;
      int dMin = n - 1;
      for (short j = 2; j <= bound; j++)
        if (n % j == 0) {
          int x = n / j;
          int y = n - x;
          int d = Math.Abs(x - y);
          if (d < dMin) {
            dMin = d;
            a = Math.Min(x, y);
            b = Math.Max(x, y);
          }
        }
      if (a == 0 && b == 0) {
        a = 1;
        b = n - 1;
      }
      ans.AppendFormat("{0} {1}", a, b);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/