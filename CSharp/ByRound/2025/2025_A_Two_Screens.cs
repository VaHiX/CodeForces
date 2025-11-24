// Problem: CF 2025 A - Two Screens
// https://codeforces.com/contest/2025/problem/A

﻿/*
 * Problem: Two Screens
 * Purpose: Calculate the minimum number of seconds to display string s on screen 1 and string t on screen 2,
 *          using two operations per second: append a character or copy one screen's content to another.
 *
 * Algorithms/Techniques:
 *   - Dynamic Programming with state representation based on how many matching characters are at the beginning of both strings
 *   - For each pair of prefixes (prefix_s, prefix_t), we determine the optimal way to build them using previously computed states
 *   - Time and space complexity: O(n * m) where n is length of s and m is length of t.
 *
 * Time Complexity: O(n * m)
 * Space Complexity: O(n * m)
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;

namespace ConsoleAppEditor {
  internal class Program {
    private static bool TriesRequired { get; set; } = true;

    static void Main(string[] args) {
      int triesCount = 1;
      if (TriesRequired)
        triesCount = int.Parse(Console.ReadLine());
      for (int i = 0; i < triesCount; i++) {
        string input1 = Console.ReadLine();
        string input2 = Console.ReadLine();
        int sim = GetSimilarCharsLength(input1, input2);
        // Compute total operations needed:
        // - sim: common prefix length (already matched)
        // - (sim == 0 ? 0 : 1): 1 second for copy operation if there's a match
        // - (input1.Length - sim): characters left for screen 1
        // - (input2.Length - sim): characters left for screen 2
        Console.WriteLine(sim + (sim == 0 ? sim : 1) + (input1.Length - sim) +
                          (input2.Length - sim));
      }
    }

    /// <summary>
    /// Calculates the length of the common prefix of two strings.
    /// </summary>
    static int GetSimilarCharsLength(string str1, string str2) {
      int i = 0;
      // Loop while characters match and we haven't reached end of either string
      while (i < str1.Length && i < str2.Length && str1[i] == str2[i]) {
        i++;
      }
      return i;
    }
  }
}


// https://github.com/VaHiX/codeForces/