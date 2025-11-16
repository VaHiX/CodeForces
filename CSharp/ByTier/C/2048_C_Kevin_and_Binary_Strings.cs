// Problem: CF 2048 C - Kevin and Binary Strings
// https://codeforces.com/contest/2048/problem/C

﻿/*
 * Problem: Kevin and Binary Strings
 * Purpose: Find two non-empty substrings of a given binary string such that their XOR value is maximized.
 * 
 * Algorithm/Techniques:
 * - Greedy approach based on the observation that to maximize XOR, we want to make the leftmost bit different.
 * - Since the string starts with '1', we look for the first '0' to find a suffix that could be XORed with prefix.
 * - We then iterate through all possible prefixes before the first '0' and calculate XOR with the suffix,
 *   keeping track of the maximum XOR result.
 *   
 * Time Complexity: O(n^2) where n is the length of the string. In the worst case, we scan the string multiple times
 *                   and perform string operations that can be up to O(n) in length.
 * Space Complexity: O(n) for storing substrings and the result string during XOR computation.
 */
using System;
using System.Text;
namespace Cf {
internal class Program2048c {
  static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    while (count-- > 0) {
      Maxxor(Console.ReadLine());
    }
  }
  public static void Maxxor(string s) {
    int i = 0, len = s.Length;
    // Find the first occurrence of '0' in the string
    while (i < len && s[i] != '0')
      ++i;
    // If there is no '0', it means the string is all 1s
    if (i == len)
      Console.WriteLine(1 + " " + len + " " + 1 + " " + 1);
    else {
      // Calculate the length of the suffix starting from the first '0'
      int cd = len - i, maxIdx = -1;
      // Take the suffix starting from first '0' as a base
      string s1 = s.Substring(i, cd), s2, max = "0";
      // Try all prefixes from 0 to (i-1) and compute their XOR with the suffix
      for (int j = 0; j < i; ++j) {
        s2 = Xor(s1, s.Substring(j, cd));
        // If current XOR is greater than max, update max and index
        if (s2.CompareTo(max) > 0) {
          maxIdx = j;
          max = s2;
        }
      }
      // Output the indices for the two substrings
      Console.WriteLine(1 + " " + len + " " + (maxIdx + 1) + " " +
                        (maxIdx + cd));
    }
  }
  public static string Xor(string s1, string s2) {
    StringBuilder sb = new StringBuilder();
    // XOR each bit from s1 and s2 and append to the result
    for (int i = 0; i < s2.Length; ++i) {
      sb.Append(s1[i] == s2[i] ? '0' : '1');
    }
    return sb.ToString();
  }
}
}


// https://github.com/VaHiX/CodeForces/