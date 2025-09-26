// Problem: CF 2134 A - Painting With Two Colors
// https://codeforces.com/contest/2134/problem/A

/*
 * Problem: Painting With Two Colors
 * 
 * Purpose: Determine if there exists a way to paint two consecutive segments of lengths 'a' and 'b'
 *          on a row of 'n' cells such that the final coloring is symmetric.
 * 
 * Algorithm:
 *   - For symmetry, the pattern from left to right must mirror the pattern from right to left.
 *   - If b >= a, we can try to align the segments so that they are symmetrically placed.
 *     - We need to check parity conditions of n, a, and b.
 *   - If b < a, both segments must start at positions that ensure symmetry,
 *     - This requires careful consideration of how the segments overlap/mirror each other.
 * 
 * Time Complexity: O(1) - Each test case is processed in constant time.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

using System.Text;

namespace AA;
class Program {
  static bool Solve() {
    long n = Next(); // Read number of cells
    long a = Next(); // Read length of red segment
    long b = Next(); // Read length of blue segment
    
    if (b >= a) {
      // When b >= a, we can place segments such that one is centered or offset in a symmetric fashion.
      // The key insight is that n and b must have the same parity for a symmetric solution to exist.
      return n % 2 == b % 2;
    }
    // When b < a, both segments need careful alignment. 
    // The necessary and sufficient condition is that n has the same parity as both a and b.
    return n % 2 == a % 2 && n % 2 == b % 2;
  }

  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++) {
      writer.WriteLine(Solve() ? "YES" : "NO"); // Output result for each test case
    }
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
    } while (c < '0' || c > '9'); // Skip non-digit characters until digit found
    res = c - '0'; // Convert first digit to number
    while (true) {
      c = reader.Read(); // Read next character
      if (c < '0' || c > '9') // If not a digit, return the constructed number
        return m * res;
      res *= 10;
      res += c - '0'; // Append to result
    }
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/