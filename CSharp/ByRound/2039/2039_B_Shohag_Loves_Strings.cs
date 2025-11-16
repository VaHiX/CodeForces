// Problem: CF 2039 B - Shohag Loves Strings
// https://codeforces.com/contest/2039/problem/B

/*
 * Problem: B. Shohag Loves Strings
 * 
 * Purpose: Given a string s, find a substring p such that the number of distinct non-empty substrings of p is even.
 *          If no such substring exists, output -1.
 * 
 * Algorithm/Techniques:
 * - The number of distinct substrings of a string of length n is at most n*(n+1)/2.
 * - For a string of length 1, there is exactly 1 distinct substring (odd).
 * - For a string of length 2, if both characters are same, there are 2 distinct substrings (even).
 * - For a string of length 3, if all characters are different, there are 6 distinct substrings (even).
 * - If no such valid substring is found, return "-1".
 *
 * Time Complexity: O(n) where n is the length of the input string.
 * Space Complexity: O(1) - only a few variables used, no extra data structures.
 */

using System;
public class ShohagLovesStrings {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string s = Console.ReadLine();
      // Check if the entire string is of length 2 and both characters are the same
      bool existSolution = s.Length == 2 && s[0] == s[1];
      // Index and length of the solution substring
      int idx = 0;
      byte len = Convert.ToByte(existSolution ? 2 : 0);
      // Iterate from index 1 to n-2 to find a valid substring
      for (int j = 1; j < s.Length - 1 && !existSolution; j++) {
        // If two consecutive characters are same, we can form a valid substring of length 2
        if (s[j - 1] == s[j]) {
          existSolution = true;
          idx = j - 1;
          len = 2;
        } else if (s[j] == s[j + 1]) {
          // If two consecutive characters after j are same
          existSolution = true;
          idx = j;
          len = 2;
        } else if (s[j - 1] != s[j] && s[j] != s[j + 1] &&
                   s[j - 1] != s[j + 1]) {
          // If three adjacent characters are all distinct, form a valid substring of length 3
          existSolution = true;
          idx = j - 1;
          len = 3;
        }
      }
      // Output the substring if valid, otherwise -1
      Console.WriteLine(existSolution ? s.Substring(idx, len) : "-1");
    }
  }
}


// https://github.com/VaHiX/CodeForces/