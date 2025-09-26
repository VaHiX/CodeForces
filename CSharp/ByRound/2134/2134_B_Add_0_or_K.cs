// Problem: CF 2134 B - Add 0 or K
// https://codeforces.com/contest/2134/problem/B

/*
B. Add 0 or K
Purpose:
This program takes an array of positive integers and a value k, then modifies each element 
by adding either 0 or k such that the GCD (Greatest Common Divisor) of all elements becomes greater than 1.
The approach uses the fact that if we can make all numbers divisible by a prime p > 1,
the GCD will be at least p.

Approach:
- If k is odd, for each element in the array:
    - If it's odd, add k to make it even; otherwise leave it as is.
      Then output modified values.
- If k is even, then use a trick involving modulo arithmetic:
    - For each element, determine its remainder when divided by (k + 1).
      Use this to compute additions that help ensure the final GCD > 1.

Time Complexity: O(n) per test case where n is the length of the array.
Space Complexity: O(n) for storing the input array and output.

Algorithms/Techniques:
- Modular arithmetic
- GCD properties

*/

using System.Text;
namespace Add0orK;
class Program {
  static void Solve() {
    long n = Next();
    long k = Next();
    long[] a = new long[n];
    for (int i = 0; i < n; i++)
      a[i] = Next();
    if (k % 2 == 1) { // If k is odd
      foreach (var i in a) {
        if (i % 2 == 1) { // If element is odd
          writer.Write(i + k); // Add k to make it even
        } else {
          writer.Write(i); // Keep it as is
        }
        writer.Write(' '); // Separator
      }
      writer.WriteLine(); // New line after processing the array
    } else { // If k is even
      long w = k + 1; // w represents a base for modular operations
      foreach (var i in a) {
        long p = i % w; // Compute remainder when divided by w
        writer.Write(i + p * k); // Modify based on the calculation
        writer.Write(' '); // Separator
      }
      writer.WriteLine(); // New line after processing the array
    }
  }
  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      Solve(); // Process each test case
    writer.Flush(); // Flush output buffer
  }
  static long Next() {
    int c;
    int m = 1;
    long res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1; // Handle negative numbers
    } while (c < '0' || c > '9'); // Skip until digit is found
    res = c - '0'; // Get first digit
    while (true) {
      c = reader.Read(); // Read next character
      if (c < '0' || c > '9') // If not a digit, return result
        return m * res;
      res *= 10; // Multiply current result by 10
      res += c - '0'; // Add new digit to result
    }
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/