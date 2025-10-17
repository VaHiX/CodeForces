// Problem: CF 1950 C - Clock Conversion
// https://codeforces.com/contest/1950/problem/C

/*
 * Problem: Clock Conversion
 * 
 * Purpose: Convert time from 24-hour format to 12-hour format.
 * 
 * Algorithm:
 *   - Split input string by ':' to get hours and minutes.
 *   - Determine AM/PM based on hour (0-11 = AM, 12-23 = PM).
 *   - Adjust hours for 12-hour format:
 *     - Hour 0 becomes 12 (for AM).
 *     - Hours 13-23 are reduced by 12.
 *     - Hours 1-12 remain the same.
 *   - Output formatted string with leading zeros preserved.
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), ignoring input/output storage.
 */

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Trim().Split(':'); // Split time into hour and minute parts
      int hh = int.Parse(parts[0]); // Parse hour
      int mm = int.Parse(parts[1]); // Parse minute
      string period = hh < 12 ? "AM" : "PM"; // Determine AM or PM
      hh = hh == 0 ? 12 : (hh > 12 ? hh - 12 : hh); // Adjust hour for 12-hour format
      Console.WriteLine($"{hh:D2}:{mm:D2} {period}"); // Output formatted time
    }
  }
}


// https://github.com/VaHiX/CodeForces/