// Problem: CF 1709 C - Recover an RBS
// https://codeforces.com/contest/1709/problem/C

/*
 * Problem: Recover an RBS (Regular Bracket Sequence)
 * 
 * Algorithm:
 * - For each test case, we need to determine if there's a unique way to replace '?' with '(' or ')' 
 *   to form a valid regular bracket sequence.
 * 
 * Approach:
 * 1. Count the number of '(' and ')' brackets.
 * 2. Calculate how many '?' need to be '(' and how many need to be ')'.
 * 3. Use greedy approach to check if we can uniquely assign '?' to maintain valid bracket structure.
 * 
 * Time Complexity: O(n) where n is the length of input string (linear scan).
 * Space Complexity: O(n) for storing input string and auxiliary variables.
 * 
 * Techniques:
 * - Greedy matching and validation
 * - Counting and balancing of brackets
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
      var s = Console.ReadLine().ToList();
      bool can = false;
      int diff = s.Where(r => r == ')').Count() - s.Where(r => r == '(').Count(); // Difference between closing and opening brackets
      int unknown = s.Where(r => r == '?').Count(); // Count of question marks
      int forcedOpen = diff + (unknown - diff) / 2; // Number of opening brackets we must place
      int forcedClosed = (unknown - diff) / 2; // Number of closing brackets we must place
      if (Math.Min(forcedOpen, forcedClosed) == 0) {
        can = true;
        output.Add("YES");
        continue;
      }
      int o = 0, c = 0, q = 0;
      bool started = false;
      if (forcedOpen <= 1)
        started = true;
      for (int i = 0; i < s.Count; i++) {
        if (s[i] == '(')
          o++;
        else if (s[i] == ')')
          c++;
        else if (s[i] == '?') {
          q++;
        }
        if (s[i] == '?' && (q == forcedOpen - 1)) {
          started = true;
          o += q; // If we've placed enough opening brackets, we've effectively set all previous ? to '('
        }
        if (started) {
          if (s[i] == '?') {
            if (q == forcedOpen) // Current '?' is the last opening bracket we needed to place
              c++;
            else if (q == forcedOpen + 1) // Current '?' is an extra opening bracket we place
              o++;
            else if (q > forcedOpen + 1) { // Too many opening brackets, this '?' must be ')'
              c++;
              started = false; // Stop further processing, invalid condition
            }
          }
          if (c > o)
            can = true; // Invalid state reached, not a valid bracket sequence
        }
      }
      if (can)
        output.Add("YES");
      else
        output.Add("NO");
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/