// Problem: CF 2035 B - Everyone Loves Tres
// https://codeforces.com/contest/2035/problem/B

using System;
public class EveryoneLovesTres {
  /*
   * Problem: Find the smallest number of length n made of only 3s and 6s that is divisible by both 33 and 66.
   * 
   * Algorithm:
   * - A number is divisible by 33 if it's divisible by both 3 and 11.
   * - A number is divisible by 66 if it's divisible by both 6 and 11.
   * - Since 33 = 3 * 11 and 66 = 6 * 11, we need a number divisible by 11 and:
   *   - For 33: it must be divisible by 3 (sum of digits divisible by 3)
   *   - For 66: it must be divisible by 6 (even and sum divisible by 3)
   * - The key insight is that 33 and 66 are both divisible by 11.
   *   So we want a number made of 3s and 6s divisible by 11.
   * - For divisibility by 11, alternating sum of digits must be divisible by 11.
   * - Since all digits are either 3 or 6, the alternating sum can be manipulated.
   *   The easiest way to make a large number with valid alternating sum is to construct:
   *   - For even length n, prefix with '3' repeated (n-2) times and suffix with "66"
   *   - For odd n, prefix with '3' repeated (n-4) times, then "63", and then "66"
   * - Edge cases:
   *   - n = 1 or n = 3: no solution because:
   *     n = 1: both 3 and 6 are not divisible by 33.
   *     n = 3: only 363 is divisible by 33, but not by 66.
   *
   * Time Complexity: O(n) - for each test case, we generate a string of length n.
   * Space Complexity: O(n) - for storing the result string.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      short n = short.Parse(Console.ReadLine());
      string ans = string.Empty;
      if (n == 1 || n == 3)
        ans = "-1"; // Edge cases where no solution exists
      else {
        string sEnd = "66";
        // If even length, fill with 3s then append 66
        // If odd length, fill with 3s, append 63, then 66
        ans = n % 2 == 0 ? string.Concat(new string('3', n - 2), sEnd)
                         : string.Concat(new string('3', n - 4), "63", sEnd);
      }
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/