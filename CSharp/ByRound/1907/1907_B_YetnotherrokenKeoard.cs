// Problem: CF 1907 B - YetnotherrokenKeoard
// https://codeforces.com/contest/1907/problem/B

/*
 * Problem: YetAnotherBrokenKeyboard
 * Purpose: Simulate a broken keyboard where 'b' deletes the last lowercase letter and 'B' deletes the last uppercase letter.
 *          The result is the final string after all key presses are processed.
 * 
 * Algorithms/Techniques:
 *   - Use two lists to store indices of lowercase and uppercase letters typed so far.
 *   - When 'b' or 'B' is pressed, decrement the corresponding index (simulate deletion).
 *   - After processing all presses, reconstruct the string by merging the remaining lowercase and uppercase letters
 *     in the order they were typed (maintaining their relative positions).
 * 
 * Time Complexity: O(n) where n is the total length of all input strings.
 * Space Complexity: O(n) for storing indices and result string.
 */

using System;
using System.Collections.Generic;
using System.Text;

public class YetnotherrokenKeoard {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string s = Console.ReadLine();
      List<int> lower = new List<int>();  // Store indices of lowercase letters
      List<int> upper = new List<int>();  // Store indices of uppercase letters
      int idxLower = 0;                   // Current position in lower list
      int idxUpper = 0;                   // Current position in upper list
      int sLen = s.Length;
      for (int j = 0; j < sLen; j++) {
        // Process 'b' key - delete last lowercase letter
        if (s[j] == 'b')
          idxLower = Math.Max(0, idxLower - 1);
        // Process 'B' key - delete last uppercase letter
        else if (s[j] == 'B')
          idxUpper = Math.Max(0, idxUpper - 1);
        // Process lowercase letter - add to lower list
        else if (char.IsLower(s[j])) {
          if (idxLower < lower.Count)
            lower[idxLower] = j;  // Reuse existing index if possible
          else
            lower.Add(j);         // Add new index
          idxLower++;
        } else {
          // Process uppercase letter - add to upper list
          if (idxUpper < upper.Count)
            upper[idxUpper] = j;  // Reuse existing index if possible
          else
            upper.Add(j);         // Add new index
          idxUpper++;
        }
      }
      // Build final output string by merging lower and upper letters in order
      StringBuilder ans = new StringBuilder();
      int il = 0;  // Pointer for lower list
      int iu = 0;  // Pointer for upper list
      while (il < idxLower && iu < idxUpper) {
        // Pick the next character based on which was typed earlier
        if (lower[il] < upper[iu]) {
          ans.Append(s[lower[il]]);
          il++;
        } else {
          ans.Append(s[upper[iu]]);
          iu++;
        }
      }
      // Append remaining lowercase letters
      while (il < idxLower) {
        ans.Append(s[lower[il]]);
        il++;
      }
      // Append remaining uppercase letters
      while (iu < idxUpper) {
        ans.Append(s[upper[iu]]);
        iu++;
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/