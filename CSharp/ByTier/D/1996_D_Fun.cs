// Problem: CF 1996 D - Fun
// https://codeforces.com/contest/1996/problem/D

/*
 * Problem: Count the number of triplets (a, b, c) of positive integers such that 
 *          ab + ac + bc <= n and a + b + c <= x.
 * 
 * Algorithm:
 * - Iterate through all possible values of 'a' from 1 to x.
 * - For each 'a', iterate through all possible values of 'b' from 1 to min(x - a, n / a).
 * - For each pair (a, b), determine the maximum value of 'c' such that:
 *   - a + b + c <= x  =>  c <= x - a - b
 *   - ab + ac + bc <= n  =>  c(a + b) <= n - ab  =>  c <= (n - ab) / (a + b)
 * - Count valid values of 'c' and accumulate total count.
 * 
 * Time Complexity: O(x * sqrt(n)) in worst case due to limiting b by n/a and iterating up to x.
 * Space Complexity: O(1) - only using a few variables.
 */

using System;
using System.IO;
class Program {
  static void Main() {
    using (
        StreamReader reader = new StreamReader(
            Console
                .OpenStandardInput())) using (StreamWriter writer =
                                                  new StreamWriter(
                                                      Console
                                                          .OpenStandardOutput())) {
      writer.AutoFlush = false;
      int t = int.Parse(reader.ReadLine());
      while (t-- > 0) {
        var input = reader.ReadLine().Split();
        long n = long.Parse(input[0]);
        long x = long.Parse(input[1]);
        long count = 0;
        for (long a = 1; a <= x; ++a) {
          // Limit b based on how much 'a' contributes to the constraint ab <= n
          long b1 = (x - a < n / a) ? (x - a) : (n / a);
          for (long b = 1; b <= b1; ++b) {
            // Determine max c based on both sum and product constraints
            long c1 = (x - a - b < (n - a * b) / (a + b))
                          ? (x - a - b)
                          : (n - a * b) / (a + b);
            // Add valid count of c (ensure it's positive)
            count += (c1 > 0) ? c1 : 0;
          }
        }
        writer.WriteLine(count);
      }
      writer.Flush();
    }
  }
}


// https://github.com/VaHiX/CodeForces/