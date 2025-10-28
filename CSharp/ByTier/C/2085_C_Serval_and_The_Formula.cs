// Problem: CF 2085 C - Serval and The Formula
// https://codeforces.com/contest/2085/problem/C

/*
C. Serval and The Formula
Algorithm: XOR properties and bit manipulation
Time Complexity: O(1) per test case
Space Complexity: O(1)

This problem asks us to find a non-negative integer k such that (x + k) + (y + k) = (x + k) ⊕ (y + k).
Using the property that a + b = a ⊕ b + 2 * (a & b), we can deduce that for the equation to hold,
we must have (x + k) & (y + k) = 0. This implies k should be chosen such that all bits of (x+k) and (y+k)
are mutually exclusive.

If x == y, then (x+k) ⊕ (y+k) = 0 for any k, but (x+k) + (y+k) will be 2*k+2*x > 0 unless k = -x, which is invalid.
Thus we return -1 in that case.

Otherwise, we try to set x as the larger value and attempt to find a suitable k such that bits align properly,
to ensure (x + k) & (y + k) = 0. We compute (1L << 40) - x which is a large number where bit pattern ensures
desired property.
*/

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read x and y
      var x = long.Parse(line[0]);
      var y = long.Parse(line[1]);
      getAns(x, y); // Process the pair
    }
  }
  static void getAns(long x, long y) {
    if (x == y) { // Special case: always invalid since their XOR will be 0 but sum is positive
      Console.WriteLine(-1);
      return;
    }
    if (y > x) { // Ensure x >= y to simplify logic
      getAns(y, x);
      return;
    }
    Console.WriteLine((1L << 40) - x); // Output computed k value that satisfies the condition
  }
}


// https://github.com/VaHiX/codeForces/