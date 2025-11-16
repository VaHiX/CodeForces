// Problem: CF 1765 B - Broken Keyboard
// https://codeforces.com/contest/1765/problem/B

using System;
public class BrokenKeyboard {
  /*
   * Code Purpose:
   * This program determines whether a given word could have been typed on a broken keyboard,
   * where every other key press results in two letters being printed instead of one.
   * 
   * Algorithm:
   * - The pattern of typing follows this logic:
   *   - Odd positions (1st, 3rd, 5th, ...) = 1 letter typed
   *   - Even positions (2nd, 4th, 6th, ...) = 2 letters typed
   * - So for a word to be valid:
   *   - Characters at positions 1, 4, 7, ... (1-indexed) must match the character at the next position.
   *   - These correspond to indices 0, 3, 6, ... in 0-indexed terms.
   *   - If any such pair doesn't match, it's invalid.
   * 
   * Time Complexity: O(n), where n is the length of the string.
   * Space Complexity: O(1), only using fixed amount of variables.
   */
  public static void Main() {
    byte t = byte.Parse(Console.ReadLine()); // Read number of test cases
    for (byte i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read length of word
      string s = Console.ReadLine(); // Read the word
      bool ans = true; // Assume valid initially
      byte j = 1; // Start from index 1 (2nd character in 1-indexed)
      while (j < n && ans) {
        // Check if current character matches the next one, but only for positions that should have double letters.
        // In valid sequences, characters at positions 1,4,7... (1-indexed) are followed by duplicates.
        ans = ans && (j < n - 1 && s[j] == s[j + 1]); 
        j += 3; // Move to next relevant index (skip 2 steps to check next potential pair)
      }
      Console.WriteLine(ans ? "YES" : "NO"); // Output result
    }
  }
}

// https://github.com/VaHiX/CodeForces/