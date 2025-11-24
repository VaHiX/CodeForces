// Problem: CF 2111 A - Energy Crystals
// https://codeforces.com/contest/2111/problem/A

/*
 * Problem: A. Energy Crystals
 * Purpose: Calculate the minimum number of actions to charge three energy crystals to level x.
 *          Each action increases a crystal's energy by any positive amount, but must satisfy:
 *          for all pairs i,j: a[i] >= floor(a[j]/2)
 *          
 * Algorithm:
 *   - The key insight is that we are effectively simulating a process where the difference in 
 *     energy levels between any two crystals can be at most one (rounded down).
 *   - We use bit manipulation to determine how many operations are needed.
 *   - The formula derived from analysis: f(x) = 2*(63 - LeadingZeroCount(x)) + 3
 *   
 * Time Complexity: O(1) per test case (bit operations are constant time)
 * Space Complexity: O(1)
 */

using System;
class Program {
  // Counts the number of leading zeros in the binary representation of x
  static int LeadingZeroCount(long x) {
    int count = 0;
    for (int i = 63; i >= 0; i--) {
      if ((x & (1L << i)) == 0)  // Check if bit at position i is zero
        count++;
      else
        break;  // Stop when we hit the first set bit
    }
    return count;
  }

  // Computes the minimum number of actions using bit manipulation
  static int f(long x) { return 2 * (63 - LeadingZeroCount(x)) + 3; }

  static void Main() {
    int t = int.Parse(Console.ReadLine());  // Read number of test cases
    while (t-- > 0) {
      long x = long.Parse(Console.ReadLine());  // Read target energy level
      Console.WriteLine(f(x));  // Output result for current test case
    }
  }
}


// https://github.com/VaHiX/codeForces/