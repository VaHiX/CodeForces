// Problem: CF 2147 A - Shortest Increasing Path
// https://codeforces.com/contest/2147/problem/A

/*
 * Problem: Shortest Increasing Path
 * 
 * Description:
 * You start at (0, 0) and want to reach (x, y) in a grid. 
 * Steps follow alternating axes (x, y, x, y, ...) with strictly increasing step sizes.
 * 
 * Algorithm/Techniques:
 * - Greedy approach: Try minimum number of steps based on constraints
 * - Check cases where path is impossible first
 * - Use mathematical reasoning to decide minimum steps needed:
 *   - If y > x, we can directly move x units in x-axis and y units in y-axis in 2 steps.
 *   - If y >= 2 and x - y >= 2, we can use 3 steps (e.g., small x-step, y-step, bigger x-step)
 *   - Otherwise impossible.
 * 
 * Time Complexity: O(t), where t is number of test cases
 * Space Complexity: O(1)
*/

using System;
class Program {
  static void Main() {
    if (!int.TryParse(Console.ReadLine(), out int testCases)) // Read number of test cases
      return;
    while (testCases-- > 0) { // Process each test case
      var parts = Console.ReadLine()!.Split(); // Split input line into x and y values
      long x = long.Parse(parts[0]); // Parse x coordinate
      long y = long.Parse(parts[1]); // Parse y coordinate
      if (y > x) { // Case 1: Can reach in 2 steps since y > x
        Console.WriteLine(2);
      } else if (y >= 2 && x - y >= 2) { // Case 2: Can reach in 3 steps
        Console.WriteLine(3);
      } else { // Case 3: Impossible to reach due to strict increasing constraint
        Console.WriteLine(-1);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/