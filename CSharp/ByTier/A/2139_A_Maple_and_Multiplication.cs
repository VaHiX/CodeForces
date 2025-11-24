// Problem: CF 2139 A - Maple and Multiplication
// https://codeforces.com/contest/2139/problem/A

/*
 * Problem: A. Maple and Multiplication
 * Purpose: Determine the minimum number of operations to make two positive integers a and b equal,
 *          where each operation allows multiplying either a or b by any positive integer.
 * 
 * Algorithms/Techniques:
 *   - Mathematical analysis based on divisibility and equality conditions.
 *   - Greedy approach: If a equals b, 0 operations. If one divides the other, 1 operation.
 *     Otherwise, 2 operations are needed.
 * 
 * Time Complexity: O(1) per test case — constant time operations (no loops or recursion).
 * Space Complexity: O(1) — uses only a fixed amount of memory regardless of input size.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) { // Process each test case
      var input = Console.ReadLine().Split(); // Read and split the input line
      long a = long.Parse(input[0]); // Parse first number
      long b = long.Parse(input[1]); // Parse second number
      int result;
      if (a == b)
        result = 0; // No operations needed if a equals b
      else if (a % b == 0 || b % a == 0)
        result = 1; // One operation if one divides the other
      else
        result = 2; // Two operations otherwise
      Console.Write(result); // Output the result
      if (t > 0)
        Console.WriteLine(); // Print newline between test cases (except after last)
    }
  }
}


// https://github.com/VaHiX/codeForces/