// Problem: CF 1994 B - Fun Game
// https://codeforces.com/contest/1994/problem/B

/*
 * Problem: Fun Game
 * 
 * Algorithm/Technique:
 * - This problem uses a key observation based on the nature of the allowed operations.
 *   The operation allows replacing elements in sequence s using XOR with earlier elements in a sliding window.
 *   By analyzing the first occurrence of '1' in both sequences, we can determine if transformation is possible.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the sequences.
 *   - The algorithm performs a single pass through the strings to find the first '1'.
 * Space Complexity: O(1) - only constant extra space is used.
 * 
 * Approach:
 * - If s equals t, the answer is always "YES".
 * - If s does not contain any '1', the only possible operation is to XOR with itself (i.e., no change),
 *   so we can only get to t if s == t, which is already checked.
 * - Otherwise, if t does not contain any '1', it's impossible to reach it since we can never create a '1' from zero.
 * - If both s and t contain a '1', we must check whether the first '1' in s occurs at or before the first '1' in t.
 *   This allows the transformation to potentially "move" the '1' in s to match the position of the '1' in t.
 * 
 * Note: The XOR operation allows propagation of information backward in a way that is determined by the index of first '1'.
 * 
 * Sample Input:
 * 6
 * 1
 * 0
 * 1
 * 7
 * 0110100
 * 0110100
 * 9
 * 100101010
 * 101111110
 * 4
 * 0011
 * 1011
 * 4
 * 0100
 * 0001
 * 8
 * 10110111
 * 01100000
 * 
 * Sample Output:
 * NO
 * YES
 * YES
 * NO
 * YES
 * YES
 */

using System;
public class FunGame {
  public static void Main() {
    short q = short.Parse(Console.ReadLine());
    for (short i = 0; i < q; i++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      string t = Console.ReadLine();
      // Check if s[0] is '1' or s == t directly
      bool ans = s[0] == '1' || s == t;
      // If not satisfied, further conditions apply
      if (!ans) {
        int idxFirst1S = s.IndexOf('1');  // Find index of first '1' in s
        int idxFirst1T = t.IndexOf('1');  // Find index of first '1' in t
        // If s has a '1' and t does not, impossible to make progress
        // Or if s's first '1' is at or before t's first '1', transformation possible
        ans = idxFirst1S > -1 && (idxFirst1T == -1 || idxFirst1S <= idxFirst1T);
      }
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/CodeForces/