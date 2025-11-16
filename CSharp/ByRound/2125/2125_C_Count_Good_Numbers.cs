// Problem: CF 2125 C - Count Good Numbers
// https://codeforces.com/contest/2125/problem/C

/* 
 * Problem: Count Good Numbers
 * Purpose: Given a range [l, r], count how many integers in that range are "good".
 *          A number is good if all prime factors of it have at least two digits (i.e., >= 10).
 * 
 * Approach:
 * - Use inclusion-exclusion principle to count numbers divisible by primes < 10.
 * - Subtract from total counts those numbers divisible by any of the small primes (2,3,5,7),
 *   but add back those divisible by products of two such primes,
 *   and so on up to all combinations of 6 primes (2,3,5,7,11,13), etc.
 *   The key insight is that only primes ≥ 10 contribute to "bad" numbers.
 * 
 * Time Complexity: O(1) per test case — constant number of operations due to fixed set of primes
 * Space Complexity: O(1) — no extra space used beyond variables
 */

using System.Text;

namespace CountGoodNumbers {
  class Program {
    static long Solve() {
      long l = Next();
      long r = Next();
      return Less(r) - Less(l - 1); // Use inclusion-exclusion for range [l,r]
    }

    static long Less(long l) {
      // Inclusion-exclusion principle
      // Count numbers <= l that are divisible by at least one prime < 10
      return l - Less(l, 2) - Less(l, 3) - Less(l, 5) - Less(l, 7) + Less(l, 6) +
             Less(l, 10) + Less(l, 14) + Less(l, 15) + Less(l, 21) + Less(l, 35) -
             Less(l, 30) - Less(l, 42) - Less(l, 70) - Less(l, 105) +
             Less(l, 210);
    }

    static long Less(long l, long p) { return l / p; } // Count multiples of p up to l

    static void Main(string[] args) {
      long t = Next(); // Read number of test cases
      for (int i = 0; i < t; i++)
        writer.WriteLine(Solve());
      writer.Flush();
    }

    static long Next() {
      int c;
      int m = 1;
      long res = 0;
      do {
        c = reader.Read();
        if (c == '-')
          m = -1;
      } while (c < '0' || c > '9');
      res = c - '0';
      while (true) {
        c = reader.Read();
        if (c < '0' || c > '9')
          return m * res;
        res *= 10;
        res += c - '0';
      }
    }

    static readonly StreamReader reader = new(
        Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer =
        new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
  }
}


// https://github.com/VaHiX/codeForces/