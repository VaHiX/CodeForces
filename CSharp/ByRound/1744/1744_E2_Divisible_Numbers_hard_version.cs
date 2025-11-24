// Problem: CF 1744 E2 - Divisible Numbers (hard version)
// https://codeforces.com/contest/1744/problem/E2

/*
Purpose: 
This code solves the problem of finding two integers x and y such that:
1. a < x <= c
2. b < y <= d
3. x * y is divisible by a * b

The approach involves:
- Finding all divisors of a and b
- For each pair of divisors (d1, d2) of a and b respectively,
  compute x = d1 * d2 and y = (a/d1) * (b/d2).
  Then adjust x and y to fit within bounds [a+1,c] and [b+1,d]
  and check if they satisfy the conditions.

Time Complexity: O(sqrt(a) * sqrt(b) + sqrt(a) * sqrt(b) * log(sqrt(a) * sqrt(b)))
Space Complexity: O(sqrt(a) + sqrt(b))

Algorithms/Techniques:
- Divisor finding using square root optimization
- Enumeration of divisors to find valid combination
- Mathematical computation for adjusting values within constraints
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
    for (int z = 0; z < fyt; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      List<long> o = new List<long>();
      List<long> a1 = new List<long>() { 1, a[0] }; // Divisors of a
      List<long> a2 = new List<long>() { 1, a[1] }; // Divisors of b
      // Find all divisors of a
      for (int i = 2; i < Math.Sqrt(a[0] + 1); i++) {
        if (a[0] % i == 0) {
          a1.Add(i);
          if (i * i != a[0])
            a1.Add(a[0] / i);
        }
      }
      // Find all divisors of b
      for (int i = 2; i < Math.Sqrt(a[1] + 1); i++) {
        if (a[1] % i == 0) {
          a2.Add(i);
          if (i * i != a[1])
            a2.Add(a[1] / i);
        }
      }
      a1 = a1.OrderBy(i => i).ToList(); // Sort divisors of a
      a2 = a2.OrderBy(i => i).ToList(); // Sort divisors of b
      long x = -1;
      long y = -1;
      bool bro = false;
      // Try all combinations of divisor pairs
      for (int i = 0; i < a1.Count; i++) {
        for (int j = 0; j < a2.Count; j++) {
          var x1 = a1[i] * a2[j]; // Compute potential x
          var y1 = (a[0] / a1[i]) * (a[1] / a2[j]); // Compute potential y
          // Adjust x to fit in [a+1, c] if needed
          if (x1 <= a[0]) {
            x1 = x1 * (a[0] / x1 + 1);
          }
          // Adjust y to fit in [b+1, d] if needed
          if (y1 <= a[1]) {
            y1 = y1 * (a[1] / y1 + 1);
          }
          // Check if both values are within the required bounds
          if (x1 <= a[2] && y1 <= a[3]) {
            x = x1;
            y = y1;
            bro = true;
            break;
          }
        }
        if (bro)
          break;
      }
      o.Add(x);
      o.Add(y);
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/