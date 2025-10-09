// Problem: CF 2094 D - Tung Tung Sahur
// https://codeforces.com/contest/2094/problem/D

/*
 * Problem: Determine if string s could be the result of hitting drums according to pattern p.
 * Each character in p represents a drum hit (L or R), which can produce either one or two sounds.
 * Algorithm:
 *   1. Parse each string into a list of runs: (character, count)
 *   2. For each run in p and s:
 *      - Characters must match
 *      - Count in s must be between count in p and 2 * count in p
 * Time Complexity: O(n) where n is total length of all strings in input
 * Space Complexity: O(n) for storing the parsed runs
 */

using System.Collections.Generic;
using System;
public class P {
  public char c { get; set; }
  public int t { get; set; }
}
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var p = Console.ReadLine().Trim();
      var s = Console.ReadLine().Trim();
      getAns(p, s);
    }
  }
  static List<P> calc(string s) {
    var res = new List<P>();
    var n = s.Length;
    var count = 1;
    for (int i = 1; i < n; i++) {
      if (s[i - 1] == s[i])
        count++;
      else {
        res.Add(new P { c = s[i - 1], t = count });
        count = 1;
      }
    }
    res.Add(new P { c = s[n - 1], t = count });
    return res;
  }
  static void getAns(string p, string s) {
    var psp = calc(p); // Parse pattern into runs
    var pss = calc(s); // Parse sound into runs
    var n = psp.Count;
    if (n != pss.Count) { // If number of runs don't match, impossible
      Console.WriteLine("NO");
      return;
    }
    for (int i = 0; i < n; i++) {
      if (psp[i].c != pss[i].c) { // Characters must match
        Console.WriteLine("NO");
        return;
      }
      if (psp[i].t * 2 < pss[i].t) { // Sound count can't exceed double pattern count
        Console.WriteLine("NO");
        return;
      }
      if (psp[i].t > pss[i].t) { // Pattern count can't exceed sound count
        Console.WriteLine("NO");
        return;
      }
    }
    Console.WriteLine("YES");
  }
}


// https://github.com/VaHiX/codeForces/