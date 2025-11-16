// Problem: CF 2030 B - Minimise Oneness
// https://codeforces.com/contest/2030/problem/B

using System;

public class MinimiseOneness {
  /*
   * Purpose: To find a binary string of length n such that the oneness (absolute difference between 
   *          f(t) and g(t)) is minimized.
   * 
   * Algorithm/Techniques:
   * - The key insight is to balance the number of subsequences with only 0s (f(t)) and those with at least one 1 (g(t)).
   * - For a string of length n:
   *   - If we place a '1' at the second position (index 1), the string becomes something like "01...".
   *   - This creates exactly one subsequence of 0s ('0'), and two subsequences that contain at least one '1' ('01' and '1').
   *   - Therefore, f(t) = 1, g(t) = 2, giving oneness = |1 - 2| = 1.
   * - For odd lengths > 1, we can still use this pattern to keep f(t) and g(t) close.
   * 
   * Time Complexity: O(n) per test case (linear in the length of string).
   * Space Complexity: O(n) for storing the character array to build the string.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      char[] digits = new char[n];
      for (int j = 0; j < n; j++)
        digits[j] = '0';  // Initialize all digits to '0'
      if (n > 1)
        digits[1] = '1';  // Place '1' at second position to balance f(t) and g(t)
      string ans = new string(digits);
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/