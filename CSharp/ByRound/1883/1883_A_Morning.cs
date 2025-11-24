// Problem: CF 1883 A - Morning
// https://codeforces.com/contest/1883/problem/A

/*
 * Code Purpose:
 * This program calculates the minimum number of seconds required to enter a 4-digit PIN code
 * on a device where the cursor can move between adjacent digits (0-9 represented linearly).
 * The cursor starts at '1'.
 * 
 * Algorithms/Techniques:
 * - Greedy approach: For each digit in the PIN, calculate the minimal distance from the current
 *   cursor position to the next required digit.
 * - Distance calculation:
 *   - For digits 0 and 9, the adjacent digits are 9 and 1 (wrapping around).
 *   - For other digits, adjacent digits are one less and one more (e.g., 5's neighbors are 4 and 6).
 * 
 * Time Complexity: O(n * t), where n is the length of the PIN (4) and t is the number of test cases.
 * Space Complexity: O(t), for storing the output strings.
 */

using System;
using System.Text;
public class Morning {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string pin = Console.ReadLine();
      byte ansi = 4; // Start at '1' (which takes 1 press + 3 more presses for 4 digits = 4 total)
      char p = '1'; // Start cursor position
      for (byte j = 0; j < 4; j++) {
        char pNext = pin[j]; // Next digit to input
        // Check for special case with 0 and 9 (wrapping around)
        if ((p == '0' || pNext == '0') && p != pNext)
          ansi += Convert.ToByte(10 - Math.Abs(pNext - p)); // Calculate min distance including wraparound
        else
          ansi += Convert.ToByte(Math.Abs(pNext - p)); // Regular distance calculation
        p = pNext; // Update cursor position
      }
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/