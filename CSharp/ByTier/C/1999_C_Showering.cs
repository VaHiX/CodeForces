// Problem: CF 1999 C - Showering
// https://codeforces.com/contest/1999/problem/C

/*
 * Problem: Determine if Alex can shower given busy intervals and shower duration.
 * Algorithm:
 *   - Sort intervals by start time (already given as non-overlapping and in order).
 *   - Check for gaps between consecutive intervals.
 *   - Also check the gap at the end of the day.
 *   - Time Complexity: O(n), where n is the number of intervals.
 *   - Space Complexity: O(n), for storing intervals.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] input = Console.ReadLine().Split(' ');
      int N = int.Parse(input[0]); // Number of tasks
      int S = int.Parse(input[1]); // Shower duration needed
      int M = int.Parse(input[2]); // Total minutes in a day
      int[] intervals = new int[N * 2]; // Store intervals as [start1, end1, start2, end2, ...]
      for (int j = 0; j < N; j++) {
        input = Console.ReadLine().Split(' ');
        intervals[j * 2] = int.Parse(input[0]); // Start time of task j
        intervals[j * 2 + 1] = int.Parse(input[1]); // End time of task j
      }
      Console.WriteLine(CanShower(intervals, S, M) ? "YES" : "NO"); // Output result
    }
  }
  static bool CanShower(int[] intervals, int s, int m) {
    int prevEnd = 0; // Tracks the end time of the previous interval
    for (int i = 0; i < intervals.Length; i += 2) {
      // Check if there's a gap between the previous interval and current one
      if (intervals[i] - prevEnd >= s)
        return true; // Found a gap large enough for shower
      prevEnd = intervals[i + 1]; // Update previous interval's end time
    }
    // Check for a gap at the end of the day
    return m - prevEnd >= s;
  }
}


// https://github.com/VaHiX/CodeForces/