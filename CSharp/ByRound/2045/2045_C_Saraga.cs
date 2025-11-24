// Problem: CF 2045 C - Saraga
// https://codeforces.com/contest/2045/problem/C

﻿/*
 * Problem: C. Saraga
 * 
 * Algorithm/Techniques:
 * - Preprocessing: For each string S and T, we precompute the first occurrence of each character from the start of S and the last occurrence of each character from the end of T.
 * - Matching: For every character that appears in both S and T, we calculate the minimum length of an interesting abbreviation using that character as a common point.
 * - Optimization: Use arrays of size 26 to track character positions, allowing O(1) lookup for each character.
 * 
 * Time Complexity: O(|S| + |T|) where |S| and |T| are the lengths of the two input strings.
 * Space Complexity: O(1) as we use fixed-size arrays of 26 elements for character tracking.
 */

using System;
namespace Cf {
internal class Program {
  static void Main(string[] args) {
    string s = GetStr(Console.ReadLine(), Console.ReadLine());
    Console.WriteLine(s == null ? "-1" : s);
  }
  
  public static string GetStr(string s1, string s2) {
    // Arrays to store the first occurrence of each character in s1 and last occurrence in s2
    int[] a1 = new int[26], a2 = new int[26];
    
    // Traverse s1 from left to right to record first occurrence of each character
    for (int i = 1; i < s1.Length; ++i) {
      // Only update if this character hasn't been seen before in s1
      if (a1[s1[i] - 'a'] == 0)
        a1[s1[i] - 'a'] = i + 1;
    }
    
    // Traverse s2 from right to left to record last occurrence of each character
    for (int j = s2.Length - 2; j >= 0; --j) {
      // Only update if this character hasn't been seen before in s2
      if (a2[s2[j] - 'a'] == 0)
        a2[s2[j] - 'a'] = j + 1;
    }
    
    // Variables to track the minimum length and the character index used
    int min = int.MaxValue, minIdx = -1;
    
    // Check all characters (from 'a' to 'z') for possible matches
    for (int i = 0; i < 26; ++i) {
      // If a character exists in both strings
      if (a1[i] != 0 && a2[i] != 0) {
        // Calculate the length of abbreviation using this character as split point
        int currentLength = a1[i] + s2.Length - a2[i];
        // Update minimum if current is smaller
        if (min > currentLength) {
          min = currentLength;
          minIdx = i;
        }
      }
    }
    
    // If no common character found, it's impossible to form an interesting abbreviation
    if (minIdx == -1)
      return null;
    
    // Build and return the optimal abbreviation:
    // Prefix from s1 up to a1[minIdx] (exclusive)
    // Suffix from s2 starting at a2[minIdx]
    return s1.Substring(0, a1[minIdx]) + s2.Substring(a2[minIdx]);
  }
}
}


// https://github.com/VaHiX/CodeForces/