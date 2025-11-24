// Problem: CF 2070 A - FizzBuzz Remixed
// https://codeforces.com/contest/2070/problem/A

/*
 * FizzBuzz Remixed Problem
 * 
 * Purpose: Count how many integers from 0 to n (inclusive) have the same remainder when divided by 3 and 5.
 * 
 * Algorithm:
 * - For any integer i, if i % 3 == i % 5, then it's a "FizzBuzz" number.
 * - The key insight is that this happens when i % 15 == 0 or when the remainders are equal (i.e., 0, 1, 2 for mod 3 and 0, 1, 2 for mod 5),
 *   but only where those two remainders match.
 * - We use a cycle-based approach: every 15 numbers form a complete cycle with 4 such numbers:
 *   0 % 3 == 0, 0 % 5 == 0
 *   1 % 3 == 1, 1 % 5 == 1
 *   2 % 3 == 2, 2 % 5 == 2
 *   3 % 3 == 0, 3 % 5 == 3 → Not matching
 *   ...
 *   The valid numbers in a cycle are 0, 1, 2 and 15 (since 15 % 3 = 0, 15 % 5 = 0), total 4 per cycle.
 * - Calculate full cycles: n / 15 and multiply by 4
 * - Then examine remaining numbers from the start of last cycle to n
 *
 * Time Complexity: O(1) - Only constant time operations
 * Space Complexity: O(1) - Uses only a few variables
 */

using System;
class FizzBuzzCount {
  static int CountFizzBuzz(int n) {
    int cycles = n / 15; // Calculate number of complete 15-number cycles
    int count = 3 * cycles; // Each cycle contributes 3 such numbers (0,1,2), except one more case added below for 15 itself
    int remainderStart = cycles * 15; // Start index of the incomplete cycle
    for (int i = remainderStart; i <= n; i++) { // Iterate through remaining elements
      if (i % 3 == i % 5) { // Check if remainders match
        count++;
      }
    }
    return count;
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()); // Read current n value
      Console.WriteLine(CountFizzBuzz(n)); // Output result for this n
    }
  }
}


// https://github.com/VaHiX/codeForces/