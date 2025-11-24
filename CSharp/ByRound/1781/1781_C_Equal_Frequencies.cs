// Problem: CF 1781 C - Equal Frequencies
// https://codeforces.com/contest/1781/problem/C

﻿/*
Problem: Equal Frequencies
Purpose: Given a string s of lowercase English letters, find a balanced string t of the same length that differs from s in as few positions as possible.
Approach:
  - For each possible number of occurrences (divisor of n), determine the minimum changes needed to make all characters appear exactly that many times.
  - Use a greedy algorithm to redistribute character counts to achieve the target frequency.
  - Construct the resulting string by replacing characters that need to be changed.

Time Complexity: O(n^2) - For each divisor of n, we process all 26 characters.
Space Complexity: O(n) - Storage for frequency map and intermediate structures.
*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < fyt; z++) {
      var n = int.Parse(Console.ReadLine());
      var s = Console.ReadLine();
      long o = long.MaxValue;
      StringBuilder sb = new StringBuilder();
      Dictionary<char, int> d = new Dictionary<char, int>();
      for (char c = 'a'; c <= 'z'; c++) {
        d.Add(c, 0);
      }
      for (int i = 0; i < n; i++)
        d[s[i]]++;
      var k1 = d.OrderBy(kv => kv.Value).ToList();
      List<int> allowedDividers = new List<int>();
      for (int i = 1; i < 27; i++) {
        if (n % i == 0)
          allowedDividers.Add(n / i);
      }
      Dictionary<char, LinkedList<char>> finalChanges =
          new Dictionary<char, LinkedList<char>>();
      int winningDi = 1;
      allowedDividers.ForEach(di => {
        Dictionary<char, LinkedList<char>> changes =
            new Dictionary<char, LinkedList<char>>();
        List<object[]> k = new List<object[]>();
        k1.ForEach(kv => k.Add(new object[] { kv.Key, kv.Value }));
        long o1 = 0;
        int l = 0;
        int r = 25;
        for (int i = 0; i < 26; i++) {
          if ((int)k[i][1] < di)
            l = i;
          if ((int)k[i][1] > di) {
            r = i;
            break;
          }
        }
        while (r <= 25 && l >= 0) {
          if ((int)k[l][1] == di) {
            l--;
            continue;
          }
          if ((int)k[r][1] <= di) {
            r++;
            continue;
          }
          int delta = Math.Min((int)k[r][1] - di, di - (int)k[l][1]);
          o1 += delta;
          k[r][1] = (int)k[r][1] - delta;
          k[l][1] = (int)k[l][1] + delta;
        }
        r = l;
        l = 0;
        for (int i = 0; i < 26; i++) {
          if ((int)k[i][1] > 0) {
            l = i;
            break;
          }
        }
        while (l < r) {
          if ((int)k[l][1] == 0) {
            l++;
            continue;
          }
          if ((int)k[r][1] == di) {
            r--;
            continue;
          }
          int delta = Math.Min(di - (int)k[r][1], (int)k[l][1]);
          o1 += delta;
          k[r][1] = (int)k[r][1] + delta;
          k[l][1] = (int)k[l][1] - delta;
        }
        if (o1 < o) {
          o = o1;
          winningDi = di;
        }
      });
      allowedDividers = new List<int>();
      allowedDividers.Add(winningDi);
      allowedDividers.ForEach(di => {
        Dictionary<char, LinkedList<char>> changes =
            new Dictionary<char, LinkedList<char>>();
        List<object[]> k = new List<object[]>();
        k1.ForEach(kv => k.Add(new object[] { kv.Key, kv.Value }));
        long o1 = 0;
        int l = 0;
        int r = 25;
        for (int i = 0; i < 26; i++) {
          if ((int)k[i][1] < di)
            l = i;
          if ((int)k[i][1] > di) {
            r = i;
            break;
          }
        }
        while (r <= 25 && l >= 0) {
          if ((int)k[l][1] == di) {
            l--;
            continue;
          }
          if ((int)k[r][1] <= di) {
            r++;
            continue;
          }
          int delta = Math.Min((int)k[r][1] - di, di - (int)k[l][1]);
          o1 += delta;
          k[r][1] = (int)k[r][1] - delta;
          k[l][1] = (int)k[l][1] + delta;
          if (delta > 0) {
            if (!changes.ContainsKey((char)k[r][0]))
              changes.Add((char)k[r][0], new LinkedList<char>());
            for (int j = 0; j < delta; j++) {
              changes[(char)k[r][0]].AddLast((char)k[l][0]);
            }
          }
        }
        r = l;
        l = 0;
        for (int i = 0; i < 26; i++) {
          if ((int)k[i][1] > 0) {
            l = i;
            break;
          }
        }
        while (l < r) {
          if ((int)k[l][1] == 0) {
            l++;
            continue;
          }
          if ((int)k[r][1] == di) {
            r--;
            continue;
          }
          int delta = Math.Min(di - (int)k[r][1], (int)k[l][1]);
          o1 += delta;
          k[r][1] = (int)k[r][1] + delta;
          k[l][1] = (int)k[l][1] - delta;
          if (delta > 0) {
            if (!changes.ContainsKey((char)k[l][0]))
              changes.Add((char)k[l][0], new LinkedList<char>());
            for (int j = 0; j < delta; j++) {
              changes[(char)k[l][0]].AddLast((char)k[r][0]);
            }
          }
        }
        finalChanges = changes;
      });
      for (int i = 0; i < n; i++) {
        if (finalChanges.ContainsKey(s[i])) {
          char nc = finalChanges[s[i]].Last.Value;
          sb.Append(nc);
          finalChanges[s[i]].RemoveLast();
          if (finalChanges[s[i]].Count == 0)
            finalChanges.Remove(s[i]);
        } else
          sb.Append(s[i]);
      }
      output.Add(o.ToString());
      output.Add(sb.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/