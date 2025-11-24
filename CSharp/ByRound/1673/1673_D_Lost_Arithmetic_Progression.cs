// Problem: CF 1673 D - Lost Arithmetic Progression
// https://codeforces.com/contest/1673/problem/D

/*
Code Purpose:
This code solves the problem of finding how many different finite arithmetic progressions A can exist such that the common elements of A and B form the arithmetic progression C. The solution involves checking constraints on the common difference and first term of A, then counting valid progressions based on divisors of the ratio between common differences.

Algorithms/Techniques:
- GCD computation for finding common divisors
- Mathematical analysis of arithmetic progression properties
- Enumeration of divisors to count valid progressions
- Modular arithmetic for large number handling

Time Complexity: O(sqrt(q) * log(min(q,r)) + T) where T is number of test cases
Space Complexity: O(sqrt(q)) for storing divisors
*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int hz = 0; hz < fyt; hz++) {
      var a1 =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var b1 =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToArray();
      long o = 0;
      long b = a1[0];
      long q = a1[1];
      long y = a1[2];
      long c = b1[0];
      long r = b1[1];
      long z = b1[2];
      if (r % q != 0 || c < b || c + r * (z - 1) > b + q * (y - 1) ||
          (c - b) % q != 0) {
        o = 0;
      } else {
        var t1 = r / q; // Calculate ratio of differences
        var t = r / t1; // Further calculation
        List<long> divisors = new List<long>();
        for (int i = 1; i < Math.Sqrt(t + 1); i++) {
          if (t % i == 0) {
            divisors.Add(i);
            divisors.Add(t / i);
          }
        }
        divisors = divisors.Distinct().ToList();
        for (int i = 0; i < divisors.Count; i++) {
          long d = divisors[i] * t1; // Current divisor scaled by t1
          if (d * q != r * GCD(d, q)) // Check if it's a valid common difference
            continue;
          if (c - d < b || c + r * (z - 1) + d > b + q * (y - 1)) {
            o = -1;
            break;
          } else {
            o += (r / d) * (r / d); // Add count of valid progressions
            o %= 1000000007; // Apply modulo
          }
        }
      }
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
  static int GCD(int num1, int num2) {
    int Remainder;
    while (num2 != 0) {
      Remainder = num1 % num2;
      num1 = num2;
      num2 = Remainder;
    }
    return num1;
  }
  static long GCD(long num1, long num2) {
    long Remainder;
    while (num2 != 0) {
      Remainder = num1 % num2;
      num1 = num2;
      num2 = Remainder;
    }
    return num1;
  }
}
}


// https://github.com/VaHiX/CodeForces/