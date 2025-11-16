// Problem: CF 1951 A - Dual Trigger
// https://codeforces.com/contest/1951/problem/A

/*
 * Problem: Dual Trigger
 * 
 * Algorithm/Techniques: 
 *   - Greedy approach with pattern recognition
 *   - The key insight is that we can only turn on two non-adjacent lamps at a time,
 *     which means that each operation changes the parity of the number of lamps turned on.
 *     So, if the final configuration has an odd number of 1s, it is impossible,
 *     since we can only add 2 lamps at a time.
 *   - Additionally, there's a special case:
 *     If the final configuration has exactly 2 lamps on and they are adjacent,
 *     it is also impossible as we can't perform the operation.
 *   - Also, if there's a sequence of 3 or more 1s (e.g., "111"), it's impossible,
 *     because such a configuration cannot be achieved due to constraint of non-adjacent turning on.
 * 
 * Time Complexity: O(n) for each test case, where n is the length of the string.
 * Space Complexity: O(1) - only using a few variables, no extra space proportional to input size.
 */

using System;
public class DualTrigger {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read number of lamps
      string s = Console.ReadLine(); // Read the target configuration
      byte count1 = 0;
      for (byte j = 0; j < n; j++)
        if (s[j] == '1')
          count1++; // Count total number of lamps turned on
      bool ans = (count1 % 2 == 0 && (count1 > 2 || !s.Contains("11"))); // Check conditions
      Console.WriteLine(ans ? "YES" : "NO"); // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/