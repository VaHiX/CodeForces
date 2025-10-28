// Problem: CF 2070 B - Robot Program
// https://codeforces.com/contest/2070/problem/B

/*
 * Problem: B. Robot Program
 * Purpose: Simulate a robot moving on a coordinate line according to a command sequence,
 *          where the sequence resets upon reaching position 0. Count how many times 0 is entered within k seconds.
 *
 * Algorithms/Techniques:
 * - Simulation with cycle detection
 * - Mathematical optimization for large k values using full cycles and remainder
 *
 * Time Complexity: O(n + n + (k % cycle_length)) = O(n + k % cycle_length)
 * Space Complexity: O(1)
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] vals = Console.ReadLine().Split();
      int n = int.Parse(vals[0]);
      long x = long.Parse(vals[1]);
      long k = long.Parse(vals[2]);
      string s = Console.ReadLine();
      long countResets = 0;
      long timeUsed = 0;
      long pos = x;
      bool initialReset = false;
      int initialResetTime = -1;
      
      // Simulate until first reset or k seconds pass
      for (int i = 0; i < n && timeUsed < k; i++) {
        timeUsed++;
        if (s[i] == 'L')
          pos--;
        else
          pos++;
        if (pos == 0) { // Robot reached 0, a reset occurs
          countResets++;
          initialReset = true;
          initialResetTime = (int)timeUsed;
          pos = 0;
          break;
        }
      }
      
      // If no reset occurred in the first run, output current count
      if (!initialReset) {
        Console.WriteLine(countResets);
        continue;
      }
      
      // Calculate how much time remains after initial reset
      long rem = k - initialResetTime;
      
      // Find cycle length (how often 0 is hit once a reset has occurred)
      int cycleResetTime = -1;
      pos = 0;
      for (int i = 0; i < n; i++) {
        if (s[i] == 'L')
          pos--;
        else
          pos++;
        if (pos == 0) {
          cycleResetTime = i + 1; // The cycle reset time is the index + 1
          break;
        }
      }
      
      // If no cycle found, return current count
      if (cycleResetTime == -1) {
        Console.WriteLine(countResets);
        continue;
      }
      
      // If remaining time is less than one cycle, simulate that part
      if (rem < cycleResetTime) {
        pos = 0;
        for (int i = 0; i < rem; i++) {
          if (s[i] == 'L')
            pos--;
          else
            pos++;
          if (pos == 0) { // Check at each step if we reach 0 again
            countResets++;
            break;
          }
        }
        Console.WriteLine(countResets);
        continue;
      }
      
      // Calculate number of full cycles and remaining steps
      long fullCycles = rem / cycleResetTime;
      countResets += fullCycles;
      long leftover = rem % cycleResetTime;
      
      // If there's leftover time, simulate the partial cycle
      pos = 0;
      for (int i = 0; i < leftover; i++) {
        if (s[i] == 'L')
          pos--;
        else
          pos++;
        if (pos == 0) {  // Check at each step if we reach 0 again in the partial cycle
          countResets++;
          break;
        }
      }
      
      Console.WriteLine(countResets);
    }
  }
}


// https://github.com/VaHiX/codeForces/