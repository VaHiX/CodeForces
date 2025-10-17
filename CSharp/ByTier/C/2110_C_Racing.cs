// Problem: CF 2110 C - Racing
// https://codeforces.com/contest/2110/problem/C

/*
 * Problem: Racing - Hobby-droning obstacle course solver
 * 
 * Description:
 * Given a drone that must fly through a series of obstacles, each with a height constraint,
 * determine a valid sequence of height changes (0 = no change, 1 = increase by 1) such that
 * the drone starts at height 0 and successfully passes all obstacles.
 * Some height changes are unknown (-1), which need to be filled in appropriately.
 *
 * Algorithm:
 * - Dynamic Programming with range tracking:
 *   For each obstacle, maintain the minimal and maximal possible heights the drone could be 
 *   at the start of that obstacle based on previous decisions.
 *   Then, backtrack to construct a valid solution.
 *
 * Time Complexity: O(n) per test case, where n is the number of obstacles.
 * Space Complexity: O(n) for storing arrays and DP states.
 */

using System;
using System.Collections.Generic;
class ObstacleCourseSolver {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      int obstacleCount = int.Parse(Console.ReadLine());
      int[] heightChanges =
          Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      int[] lowerBounds = new int[obstacleCount];
      int[] upperBounds = new int[obstacleCount];
      for (int i = 0; i < obstacleCount; i++) {
        string[] bounds = Console.ReadLine().Split();
        lowerBounds[i] = int.Parse(bounds[0]);
        upperBounds[i] = int.Parse(bounds[1]);
      }
      // dp[i] stores the minimum and maximum possible heights at the start of obstacle i
      (int Min, int Max)[] dp = new(int, int)[obstacleCount + 1];
      dp[0] = (0, 0);
      bool isPossible = true;
      for (int i = 1; i <= obstacleCount; i++) {
        int currentLower = lowerBounds[i - 1];
        int currentUpper = upperBounds[i - 1];
        var prev = dp[i - 1];
        int minHeight, maxHeight;
        // Determine the range of possible heights based on the height change pattern
        switch (heightChanges[i - 1]) {
        case 0: // No change in height
          minHeight = prev.Min;
          maxHeight = prev.Max;
          break;
        case 1: // Height increases by 1
          minHeight = prev.Min + 1;
          maxHeight = prev.Max + 1;
          break;
        default: // Height can increase or stay the same, so it's at least min(prev.Min) and at most prev.Max + 1
          minHeight = prev.Min;
          maxHeight = prev.Max + 1;
          break;
        }
        // Clamp the valid range to obstacle constraints
        minHeight = Math.Max(minHeight, currentLower);
        maxHeight = Math.Min(maxHeight, currentUpper);
        if (minHeight > maxHeight) {
          isPossible = false;
          break;
        }
        dp[i] = (minHeight, maxHeight);
      }
      if (!isPossible) {
        Console.WriteLine(-1);
        continue;
      }
      // Replay the solution to construct the actual array of height changes
      int[] solution = new int[obstacleCount];
      int currentHeight = dp[obstacleCount].Min;
      for (int i = obstacleCount; i >= 1; i--) {
        var prev = dp[i - 1];
        switch (heightChanges[i - 1]) {
        case 0: // This change is fixed as 0
          solution[i - 1] = 0;
          break;
        case 1: // This change is fixed as 1
          solution[i - 1] = 1;
          currentHeight -= 1;
          break;
        default: // This change is unknown, decide based on validity
          if (currentHeight >= prev.Min && currentHeight <= prev.Max) {
            solution[i - 1] = 0;
          } else {
            solution[i - 1] = 1;
            currentHeight -= 1;
          }
          break;
        }
      }
      if (currentHeight != 0) { // Root height must be 0
        Console.WriteLine(-1);
        continue;
      }
      Console.WriteLine(string.Join(" ", solution));
    }
  }
}


// https://github.com/VaHiX/codeForces/