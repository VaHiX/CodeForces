// Problem: CF 2085 A - Serval and String Theory
// https://codeforces.com/contest/2085/problem/A

// Purpose: Determine if a string can be made "universal" by swapping at most k characters.
//          A string is universal if it is lexicographically smaller than its reversal.
//          Swapping two characters is allowed at most k times.
//
// Algorithms/Techniques:
// - Check if the string is already universal (s[left] < s[right] at first differing pair)
// - If not universal and k > 0, determine if it's possible to make it universal:
//   * If string is a palindrome and all characters are same, it's impossible unless k > 0 and length > 1
//   * Otherwise, unless all characters are the same, it's always possible to make it universal with at least one swap
//
// Time Complexity: O(n) per test case, where n is the length of the string
// Space Complexity: O(1) - only using a few variables for comparison and iteration

using System;
public class ServalAndStringTheory {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      short k = short.Parse(parts[1]);
      string s = Console.ReadLine();
      // Check if already universal, or if can be made universal with k swaps
      bool ans = IsUniversal(s) || k > 0 && (!IsPalindrome(s) || !SameChars(s));
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
  
  // Check if all characters in the string are the same
  private static bool SameChars(string s) {
    bool sameChars = true;
    for (byte i = 1; i < s.Length && sameChars; i++)
      sameChars = sameChars && s[i] == s[i - 1];
    return sameChars;
  }
  
  // Check if the string is a palindrome
  private static bool IsPalindrome(string s) {
    bool isPalindrome = true;
    byte l = 0;
    byte r = Convert.ToByte(s.Length - 1);
    while (l < r && isPalindrome) {
      isPalindrome = isPalindrome && s[l] == s[r];
      l++;
      r--;
    }
    return isPalindrome;
  }
  
  // Check if the string is universal (lexicographically smaller than its reverse)
  private static bool IsUniversal(string s) {
    bool isUniversal = false;
    byte l = 0;
    byte r = Convert.ToByte(s.Length - 1);
    while (l < r && !isUniversal) {
      if (s[l] == s[r]) {
        l++;
        r--;
      } else if (s[l] < s[r])
        isUniversal = true;
      else
        break;
    }
    return isUniversal;
  }
}


// https://github.com/VaHiX/CodeForces/