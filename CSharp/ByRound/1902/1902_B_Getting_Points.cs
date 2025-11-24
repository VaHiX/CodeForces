// Problem: CF 1902 B - Getting Points
// https://codeforces.com/contest/1902/problem/B

using System;
public class GettingPoints {
  // Purpose: Calculate the maximum number of days Monocarp can rest
  //          while earning enough points to avoid expulsion.
  // Algorithm: Greedy approach with optimal task selection.
  // Time Complexity: O(1) per test case
  // Space Complexity: O(1)
  public static void Main() {
    short tc = short.Parse(Console.ReadLine());
    for (short i = 0; i < tc; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      long p = long.Parse(parts[1]);
      int l = int.Parse(parts[2]);
      int t = int.Parse(parts[3]);
      // Calculate total number of tasks available
      int numTask = (n - 1) / 7 + 1;
      // Calculate score for completing 2 tasks and 1 lesson
      long scoreTask2 = l + 2L * t;
      // Calculate maximum number of days to study for 2 tasks
      int numDayTask2Max = numTask / 2;
      // Determine how many days needed to use 2 tasks optimally
      int numDayTask2 = (int)Math.Min(
          numDayTask2Max, p / scoreTask2 + Math.Sign(p % scoreTask2));
      // Subtract the points obtained from 2-task days
      p = Math.Max(0, p - (long)numDayTask2 * scoreTask2);
      // Calculate score for completing 1 task and 1 lesson
      int scoreTask1 = l + t;
      // Calculate maximum number of days to study for 1 task
      int numDayTask1Max = numTask % 2;
      // Determine how many days needed to use 1 task
      int numDayTask1 = (int)Math.Min(
          numDayTask1Max, p / scoreTask1 + Math.Sign(p % scoreTask1));
      // Subtract the points obtained from 1-task days
      p = Math.Max(0, p - (long)numDayTask1 * scoreTask1);
      // Calculate the number of days needed for remaining lesson points
      int numDayLesson = Convert.ToInt32(p / l + Math.Sign(p % l));
      // Compute the number of rest days
      int ans = n - numDayTask1 - numDayTask2 - numDayLesson;
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/