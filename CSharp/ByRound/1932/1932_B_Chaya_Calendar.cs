// Problem: CF 1932 B - Chaya Calendar
// https://codeforces.com/contest/1932/problem/B

/*
 * Problem: Chaya Calendar
 * 
 * Purpose: 
 *   Given n signs with periodicities a_i, determine the year when the nth sign occurs,
 *   assuming signs occur sequentially and each subsequent sign starts waiting after
 *   the previous one has occurred.
 * 
 * Algorithm:
 *   - For each sign, we compute the next occurrence time based on the last sign's occurrence.
 *   - We maintain a running total 'ans' which represents the year when the previous sign occurred.
 *   - For the current sign with period a_j, we calculate:
 *     - The number of periods elapsed since the last occurrence: ans / a_j
 *     - The next occurrence after that: (ans / a_j + 1) * a_j
 *   - We repeat this for all signs.
 * 
 * Time Complexity: O(n), where n is the number of signs.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */
using System;
public class ChayaCalendar {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read number of signs
      string[] parts = Console.ReadLine().Split(); // Read periodicities
      int ans = 0; // Initialize the year of the last sign's occurrence
      for (byte j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]); // Current sign's periodicity
        // Compute next occurrence time of current sign after the previous one
        ans = (ans / aj + 1) * aj;
      }
      Console.WriteLine(ans); // Output the year when the last sign occurs
    }
  }
}


// https://github.com/VaHiX/CodeForces/