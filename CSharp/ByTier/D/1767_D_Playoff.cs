// Problem: CF 1767 D - Playoff
// https://codeforces.com/contest/1767/problem/D

﻿/*
 * Code Purpose: 
 *   This program determines which team skill levels can potentially win a playoff tournament,
 *   given the tournament structure and rules for determining winners in each phase.
 *   
 *   Key Algorithm:
 *   - The tournament structure is a binary tree where each phase halves the number of teams.
 *   - Each phase has a rule: '0' means the lower-skilled team wins, '1' means the higher-skilled team wins.
 *   - The key insight is that for a team with skill x to win, it must be able to advance through
 *     the tournament such that it can be in the final position, depending on how the tournament unfolds.
 *   - The approach involves calculating bounds on possible winning positions based on the string s.
 *   
 *   Time Complexity: O(1) - Since the computation relies on mathematical formulas and fixed-length loops
 *   Space Complexity: O(1) - The space used is constant regardless of input size
 *   
 *   The algorithm determines:
 *   - How many phases have '1' (higher skill wins):
 *   - Then calculates the minimum and maximum possible positions (skill levels) that can win:
 *   - The minimum is 2^k where k is the number of '1's in the string
 *   - The maximum is 2^n - 2^(n-k) + 1
 *   - All integers in this range are the winning teams.
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete3 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine()); // Read number of tournament levels
      var s = Console.ReadLine(); // Read the string of tournament rules
      List<long> o = new List<long>(); // List to store the winning team skill levels
      int k = s.Count(i => i == '1'); // Count how many phases follow "higher skill wins" rule
      // For each possible skill level in the valid range:
      // From 2^k to (2^n - 2^(n-k) + 1), inclusive
      for (long i = (long)Math.Pow(2, k); 
           i <= (long)(Math.Pow(2, n) - Math.Pow(2, n - k)) + 1; i++)
        o.Add(i); // Add the skill level to output list
      output.Add(string.Join(" ", o)); // Join results with spaces and add to output
    }
    string on = string.Join("\n", output); // Join all outputs
    Console.WriteLine(on); // Print final output
  }
}
}


// https://github.com/VaHiX/CodeForces/