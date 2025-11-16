// Problem: CF 1774 C - Ice and Fire
// https://codeforces.com/contest/1774/problem/C

/*
 * Problem: Ice and Fire
 * 
 * Algorithm/Technique: Simulation with Sliding Window
 * 
 * Time Complexity: O(n) where n is the number of players
 * Space Complexity: O(n) for storing the result array
 * 
 * Approach:
 * - The problem simulates a tournament where players with certain temperature values fight in environments
 *   defined by a binary string s.
 * - For each x from 2 to n, we determine how many players among those with temperature values ≤ x
 *   can potentially win the tournament.
 * - We use a sliding window approach to track how many consecutive 0s or 1s there are.
 *   - When s[i] == '0', it means lower temperature wins, so we track consecutive 0s.
 *   - When s[i] == '1', it means higher temperature wins, so we track consecutive 1s.
 * - The result for x is computed based on the current count of consecutive same characters.
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      var s = Console.ReadLine();
      List<int> o = new List<int>();
      int q0 = 0; // Count of consecutive 0s ending at current position
      int q1 = 0; // Count of consecutive 1s ending at current position
      for (int i = 0; i < n - 1; i++) {
        if (s[i] == '0') {
          q0++;
          q1 = 0; // Reset consecutive 1s count
          // The number of players who can win for x = i+2 is determined by current consecutive 0s
          o.Add(i + 2 - q0);
        } else {
          q1++;
          q0 = 0; // Reset consecutive 0s count
          // The number of players who can win for x = i+2 is determined by current consecutive 1s
          o.Add(i + 2 - q1);
        }
      }
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/