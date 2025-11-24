// Problem: CF 2098 C - Sports Betting
// https://codeforces.com/contest/2098/problem/C

/*
 * Problem: Sports Betting
 * 
 * Algorithm/Techniques:
 * - The problem revolves around determining whether Vadim can guarantee at least one correct prediction
 *   for students' bets based on the boarding process patterns.
 * - We need to check if there exists a way to assign boarding outcomes (either bus or jet bridge) 
 *   such that at least one student wins their bet.
 * - Each student's bet is on day a_i, and the win condition requires correct predictions on days a_i+1 and a_i+2.
 * - The idea is to model this as a graph coloring problem or check for overlapping ranges where at least
 *   two students are betting on consecutive days or have overlapping constraints that allow
 *   for a guaranteed win.
 * 
 * Time Complexity: O(n log n) due to sorting of keys in help2 function, where n is the number of students.
 * Space Complexity: O(n) for storing frequency map of bet days.
 */

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  // Check if any single day has 4 or more bets. If so, it's always possible to assign
  // outcomes such that at least one student wins, due to enough combinations.
  static bool help(Dictionary<long, int> freq) {
    foreach (var cnt in freq.Values) {
      if (cnt >= 4)
        return true;
    }
    return false;
  }

  // Check for 2 or more consecutive days with at least 2 bets on each. 
  // This allows for a valid assignment where both consecutive bets can be satisfied.
  static bool help2(Dictionary<long, int> freq) {
    var keys = freq.Keys.ToList();
    keys.Sort(); // Sort the keys to detect consecutive days
    int cons = 0; // Count of consecutive days with at least 2 bets
    long prev = -1000000000; // Previous day, initialized to a value far below any valid input
    foreach (var k in keys) {
      if (k != prev + 1) // If current day is not consecutive to previous
        cons = 0;
      if (freq[k] >= 2 && ++cons >= 2) // If current day has at least 2 bets and we have 2 consecutive days
        return true;
      prev = k;
    }
    return false;
  }

  // Main solving logic for each test case
  static string Solve(int n, long[] arr) {
    var freq = new Dictionary<long, int>(); // Frequency map for bet days
    foreach (var v in arr) {
      if (!freq.ContainsKey(v))
        freq[v] = 0;
      freq[v]++;
    }
    if (help(freq))
      return "Yes";
    if (help2(freq))
      return "Yes";
    return "No";
  }

  // Entry point of the program
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      var arr = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
      Console.WriteLine(Solve(n, arr));
    }
  }
}


// https://github.com/VaHiX/CodeForces/