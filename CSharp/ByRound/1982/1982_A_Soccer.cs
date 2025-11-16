// Problem: CF 1982 A - Soccer
// https://codeforces.com/contest/1982/problem/A

/*
 * Problem: Soccer
 * Purpose: Determine if it's possible that two teams never had an equal score during a soccer match,
 *          given the initial and final scores.
 *
 * Algorithm/Techniques:
 * - The key insight is that if the initial and final scores are on the same side of the diagonal
 *   (i.e., both x1 < y1 and x2 < y2, or both x1 > y1 and x2 > y2), then it is possible for the teams
 *   to never have equal scores.
 * - If the teams cross the diagonal (i.e., one score is on one side and the other is on the opposite),
 *   then at some point they must have been equal.
 *
 * Time Complexity: O(1) - We perform a constant number of operations per test case.
 * Space Complexity: O(1) - We use only a constant amount of extra space.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] line1 = Console.ReadLine().Split(); // Read initial score
      long x1 = long.Parse(line1[0]); // Parse x1
      long y1 = long.Parse(line1[1]); // Parse y1
      string[] line2 = Console.ReadLine().Split(); // Read final score
      long x2 = long.Parse(line2[0]); // Parse x2
      long y2 = long.Parse(line2[1]); // Parse y2
      // Check if both initial and final scores are on the same side of the diagonal (x == y)
      if ((x1 < y1 && x2 < y2) || (x1 > y1 && x2 > y2)) {
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/