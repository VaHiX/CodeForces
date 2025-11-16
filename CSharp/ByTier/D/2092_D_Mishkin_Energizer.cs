// Problem: CF 2092 D - Mishkin Energizer
// https://codeforces.com/contest/2092/problem/D

/*
 * Problem: Mishkin Energizer
 * 
 * Purpose: Balance a string consisting of characters L, I, T by inserting characters
 *          between adjacent differing characters such that the final string contains
 *          equal counts of each character. The operation is to insert one character
 *          between indices i and i+1 where s[i] != s[i+1]. Each insertion must use
 *          a character different from both neighbors.
 *
 * Algorithms/Techniques:
 * - Greedy insertion strategy: for each step, find an adjacent pair of different characters,
 *   derive the required insert character that helps achieve balance (by minimizing excess).
 * - If no good insertion found, fallback to any valid operation.
 * - Termination condition: when all three counts are equal or we reach maximum allowed operations.
 *
 * Time Complexity: O(n^2) per test case in worst case due to string manipulations and nested iterations.
 * Space Complexity: O(n) for storing the current string and intermediate data structures like lists/dictionaries.
 */

using System;
using System.Collections.Generic;
class Program {
  static Dictionary<char, int> GetCounts(string s) {
    var counts =
        new Dictionary<char, int> { { 'L', 0 }, { 'I', 0 }, { 'T', 0 } };
    foreach (var c in s) {
      counts[c]++; // Count occurrences of each character
    }
    return counts;
  }
  static char GetInsertChar(char c1, char c2) {
    if ((c1 == 'L' && c2 == 'I') || (c1 == 'I' && c2 == 'L'))
      return 'T'; // Inserting T balances L and I
    if ((c1 == 'L' && c2 == 'T') || (c1 == 'T' && c2 == 'L'))
      return 'I'; // Inserting I balances L and T
    if ((c1 == 'I' && c2 == 'T') || (c1 == 'T' && c2 == 'I'))
      return 'L'; // Inserting L balances I and T
    return '?';
  }
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    string s = Console.ReadLine();
    bool monochromatic = false;
    if (n > 0) {
      bool allSame = true;
      for (int i = 1; i < n; ++i) {
        if (s[i] != s[0]) {
          allSame = false;
          break;
        }
      }
      if (allSame) {
        monochromatic = true;
      }
    }
    if (monochromatic) {
      Console.WriteLine(-1);
      return;
    }
    var initialCounts = GetCounts(s);
    if (initialCounts['L'] == initialCounts['I'] &&
        initialCounts['I'] == initialCounts['T']) {
      Console.WriteLine(0);
      return;
    }
    List<int> opsIndices = new List<int>();
    int opsCount = 0;
    string currentS = s;
    int maxOps = 2 * n;
    for (int op = 0; op < maxOps; ++op) {
      var counts = GetCounts(currentS);
      if (counts['L'] > 0 && counts['L'] == counts['I'] &&
          counts['I'] == counts['T'])
        break; // Balanced state achieved
      if (currentS.Length < 2)
        break; // Cannot perform operation on string length < 2
      int minCount = Math.Min(Math.Min(counts['L'], counts['I']), counts['T']);
      List<char> desiredChars = new List<char>();
      if (counts['L'] == minCount)
        desiredChars.Add('L'); // Add character with minimum count
      if (counts['I'] == minCount)
        desiredChars.Add('I');
      if (counts['T'] == minCount)
        desiredChars.Add('T');
      int bestIndex = -1;
      char bestChar = '?';
      for (int i = 0; i < currentS.Length - 1; ++i) {
        if (currentS[i] != currentS[i + 1]) {
          char insertChar = GetInsertChar(currentS[i], currentS[i + 1]);
          if (desiredChars.Contains(insertChar)) {
            bestIndex = i;
            bestChar = insertChar;
            break; // Found a greedy insertion point
          }
        }
      }
      if (bestIndex != -1) {
        currentS = currentS.Insert(bestIndex + 1, bestChar.ToString());
        opsIndices.Add(bestIndex + 1);
        opsCount++;
      } else {
        int fallbackIndex = -1;
        char fallbackChar = '?';
        for (int i = 0; i < currentS.Length - 1; ++i) {
          if (currentS[i] != currentS[i + 1]) {
            fallbackIndex = i;
            fallbackChar = GetInsertChar(currentS[i], currentS[i + 1]);
            break;
          }
        }
        if (fallbackIndex != -1) {
          currentS =
              currentS.Insert(fallbackIndex + 1, fallbackChar.ToString());
          opsIndices.Add(fallbackIndex + 1);
          opsCount++;
        } else {
          break; // No meaningful operation possible
        }
      }
    }
    var finalCounts = GetCounts(currentS);
    if (finalCounts['L'] > 0 && finalCounts['L'] == finalCounts['I'] &&
        finalCounts['I'] == finalCounts['T']) {
      Console.WriteLine(opsCount);
      foreach (var index in opsIndices) {
        Console.WriteLine(index);
      }
    } else {
      Console.WriteLine(-1);
    }
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/