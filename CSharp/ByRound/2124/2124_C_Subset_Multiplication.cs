// Problem: CF 2124 C - Subset Multiplication
// https://codeforces.com/contest/2124/problem/C

/*
 * Problem: C. Subset Multiplication
 * 
 * Purpose:
 *   Given an array b that may have been derived from a "beautiful" array a (where each element divides the next),
 *   by multiplying some subset of elements by a positive integer x, find any valid value of x.
 *   
 * Algorithm:
 *   - For a beautiful array where a[i] divides a[i+1], we know that a[i+1]/a[i] is an integer.
 *   - Since b[i] = a[i] * x^(s[i]), where s[i] is 1 if element i was multiplied by x, otherwise 0,
 *     the ratio between consecutive elements of b can reveal information about x and subset S.
 *   - We compute LCM of all values (b[i]/gcd(b[i], b[i+1])) for which b[i+1] is not divisible by b[i].
 *     This ensures that we capture how many times x was applied in the sequence.
 *   
 * Time Complexity: O(n * log(max_element))
 *   - Preprocessing and GCD/LCM operations are logarithmic.
 * Space Complexity: O(n)
 *   - Storing input array and intermediate results.
 */

using System.Text;
namespace SubsetMultiplication;
class Program {
  static long Solve() {
    long n = Next();
    long[] a = new long[n];
    for (int i = 0; i < n; i++)
      a[i] = Next();
    long g = 1;
    for (int i = 1; i < n; i++) {
      // If current element is not divisible by previous, it means multiplication
      // by x occurred in the transition from a[i-1] to a[i].
      if (a[i] % a[i - 1] != 0) {
        // Calculate what factor was introduced (b[i]/gcd(b[i], b[i+1]))
        var p = a[i - 1] / Gcd(a[i], a[i - 1]);
        g = Lcm(g, p);
      }
    }
    return g;
  }
  public static long Lcm(long a, long b) { return (a / Gcd(a, b)) * b; }
  public static long Gcd(long a, long b) { return b == 0 ? a : Gcd(b, a % b); }
  static void Main(string[] args) {
    long t = Next();
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


// https://github.com/VaHiX/codeForces/