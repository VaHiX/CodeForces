// Problem: CF 1735 C - Phase Shift
// https://codeforces.com/contest/1735/problem/C

﻿/*
 * Problem: C. Phase Shift
 * 
 * Algorithm/Technique:
 * - This problem involves reconstructing a lexicographically smallest original string
 *   from a transformed string, where each character is shifted forward in a circular 
 *   arrangement of 26 lowercase English letters.
 * - The key insight is that we can think of shifting as a permutation of characters on a circle.
 * - We process the string from left to right and greedily assign the smallest valid character 
 *   to each position in the original string that would result in the given transformed character.
 * - To efficiently track equivalence classes of characters (i.e., which characters are mapped to each other),
 *   we use a Union-Find-like approach with dictionaries and lists.
 * 
 * Time Complexity:
 * - O(n * 26) = O(n) where n is the total length of all strings across test cases.
 *   The factor of 26 comes from checking for the minimal available character in chains.
 * 
 * Space Complexity:
 * - O(1) since we only store fixed-size data structures (26 characters, at most 26 entries in maps/sets).
 *   The space used per test case is bounded.
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = long.Parse(Console.ReadLine());
      var s = Console.ReadLine();
      List<char> o = new List<char>();
      Dictionary<char, char> map = new Dictionary<char, char>(); // Maps transformed character to original
      Dictionary<char, char> reverseMap = new Dictionary<char, char>(); // Maps original to its root (for union-find)
      Dictionary<char, List<char>> chains = new Dictionary<char, List<char>>(); // Chains of equivalent characters
      List<char> allowedOrigins = new List<char>(); // All possible original chars from 'a' to 'z'
      for (byte c = 97; c < 97 + 26; c++) {
        allowedOrigins.Add((char)c);
        chains.Add((char)c, new List<char>() { (char)c });
        reverseMap.Add((char)c, (char)c);
      }
      for (int i = 0; i < n; i++) {
        var d = s[i]; // Current transformed character
        if (!map.ContainsKey(d)) {
          var f = reverseMap[d]; // Find root of transformed character's chain
          var q = f; // Placeholder for the min character to merge with
          var w = chains.Keys.Where(k => k != f); // All other characters except the current root
          if (w.Count() > 0)
            q = w.Min(); // Find the lexicographically smallest available merge target
          chains[f].AddRange(chains[q]); // Merge q's chain into f's chain
          chains[q].ForEach(j => reverseMap[j] = f); // Update reverse map for merged elements
          chains.Remove(q); // Remove merged chain
          map.Add(d, q); // Assign q (the root of the smaller chain) as original for d
        }
        o.Add(map[d]); // Build output using mapped original character
      }
      output.Add(string.Join("", o));
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/