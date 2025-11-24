// Problem: CF 1690 F - Shifting String
// https://codeforces.com/contest/1690/problem/F

/* 
 * Problem: F. Shifting String
 * 
 * Purpose: Determine the minimum number of operations to return a string to its original form after applying a permutation.
 * 
 * Approach: 
 * 1. Each position in the string follows a cycle under the permutation.
 * 2. For each cycle, find the smallest rotation that returns the characters in that cycle to their original positions.
 * 3. The answer is the LCM of all such cycle lengths.
 * 
 * Time Complexity: O(n^2) in worst case due to finding cycles and rotations, but with small constraints (n <= 200), it's acceptable.
 * Space Complexity: O(n) for storing visited array and cycle information.
 * 
 * Algorithms/Techniques:
 * - Cycle detection in permutations
 * - Finding minimal rotation period for each cycle
 * - Computing LCM of periods
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
      var a =
          Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToArray();
      long o = 0;
      int[] visited = new int[n];
      int id = 0;
      int period = 0;
      List<int> ds = new List<int>();
      List<int> q = new List<int>();
      while (id < n) {
        if (visited[id] > 0) {
          id++;
          if (period == 0)
            continue;
          // Collect characters in current cycle
          List<char> cs = new List<char>();
          ds.ForEach(i => cs.Add(s[i]));
          string s1 = string.Join("", cs);
          string s0 = s1;
          // Find minimal rotation period for the characters in this cycle
          for (int i = 1; i <= s1.Length; i++) {
            StringBuilder sb1 = new StringBuilder();
            sb1.Append(s1.Substring(1));
            sb1.Append(s1[0]);
            string s2 = sb1.ToString();
            if (s0 == s2) {
              q.Add(i);
              break;
            }
            s1 = s2;
          }
          ds = new List<int>();
          period = 0;
          continue;
        }
        period++;
        ds.Add(id);
        visited[id] = 1;
        id = a[id] - 1; // Permutation is 1-indexed, convert to 0-indexed
      }
      o = 1;
      q = q.Distinct().ToList();
      q.ForEach(i => {
        var g = gcdExtended(o, i);
        o = (o * i) / g;
      });
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
  public static long x, y;
  public static long gcdExtended(long a, long b) {
    if (a == 0) {
      x = 0;
      y = 1;
      return b;
    }
    long gcd = gcdExtended(b % a, a);
    long x1 = x;
    long y1 = y;
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
  }
}
}


// https://github.com/VaHiX/CodeForces/