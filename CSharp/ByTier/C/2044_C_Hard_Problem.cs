// Problem: CF 2044 C - Hard Problem
// https://codeforces.com/contest/2044/problem/C

/*
C. Hard Problem
Time Complexity: O(1) per test case
Space Complexity: O(1)

Algorithms/Techniques: Greedy approach

The problem involves assigning monkeys to seats in a classroom with 2 rows and m seats each.
- 'a' monkeys prefer row 1
- 'b' monkeys prefer row 2
- 'c' monkeys have no preference

We want to maximize the total number of seated monkeys. The strategy is:
1. Assign as many as possible from row 1 preference (up to m seats)
2. Assign as many as possible from row 2 preference (up to m seats)
3. For remaining seats, assign monkeys with no preference

The solution computes:
- sum1 = min(m, a) - maximum monkeys that can be placed in row 1
- sum2 = min(m, b) - maximum monkeys that can be placed in row 2
- r = min(2 * m - sum1 - sum2, c) - remaining seats available for no-preference monkeys

Finally, we output the total number of seated monkeys.
*/

using System;
using System.Collections.Generic;
class _C_Hard_Problem {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] s = Console.ReadLine().Split(); // Read input line
      int m = int.Parse(s[0]); // Number of seats per row
      int a = int.Parse(s[1]); // Monkeys preferring row 1
      int b = int.Parse(s[2]); // Monkeys preferring row 2
      int c = int.Parse(s[3]); // Monkeys with no preference
      
      int sum1 = Math.Min(m, a); // Max monkeys to place in row 1
      int sum2 = Math.Min(m, b); // Max monkeys to place in row 2
      int r = Math.Min(2 * m - sum1 - sum2, c); // Remaining seats for no-preference monkeys
      
      Console.WriteLine(sum1 + sum2 + r); // Output total seated monkeys
    }
  }
}


// https://github.com/VaHiX/codeForces/