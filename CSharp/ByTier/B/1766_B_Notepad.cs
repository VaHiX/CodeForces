// Problem: CF 1766 B - Notepad#
// https://codeforces.com/contest/1766/problem/B

/*
Algorithm: Notepad#
Techniques: Hash Set, String Substring Matching

Time Complexity: O(n^2) in the worst case due to substring operations and hash set lookups,
                 but typically much faster in practice due to early termination.
Space Complexity: O(n^2) in the worst case, as we may store up to O(n) substrings of length 2,
                   each of which can be up to O(n) in total length.

This solution uses a greedy approach to detect whether there's any repeated pattern that allows
us to copy and paste a substring, thereby reducing the total number of operations needed.
We scan the string for repeated 2-character substrings, and if we find one, we can potentially
build the entire string using fewer operations than the length of the string.
*/

using System;
using System.Collections.Generic;
public class Notepad {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      HashSet<string> hs = new HashSet<string>(); // Store seen 2-character substrings
      int j = 0;
      bool ans = false; // Flag to indicate if a shorter way exists
      
      // Loop through the string to find repeated 2-character substrings
      while (j < n - 1 && !ans) {
        string s2 = s.Substring(j, 2); // Extract current 2-character substring
        
        if (hs.Contains(s2)) // If this substring was seen before
          ans = true; // We can form the string with fewer operations
        else {
          hs.Add(s2); // Add this substring to the set of seen substrings
          
          // Special case optimization: if the current and next 2-character substrings
          // are all identical, we can skip ahead by 2 positions
          if (j < n - 2 && s2[0] == s2[1] && s2[0] == s[j + 2])
            j += 2;
          else
            j++; // Move to next character
        }
      }
      
      Console.WriteLine(ans ? "YES" : "NO"); // Output result for current test case
    }
  }
}


// https://github.com/VaHiX/CodeForces/