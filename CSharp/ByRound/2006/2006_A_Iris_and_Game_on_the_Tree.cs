// Problem: CF 2006 A - Iris and Game on the Tree
// https://codeforces.com/contest/2006/problem/A

/*
 * Problem: Iris and Game on the Tree
 * 
 * Purpose:
 *   Determine the final score of a tree game where players (Iris and Dora) alternately assign 0 or 1 to '?' vertices,
 *   with Iris trying to maximize the score and Dora minimizing it. The score is defined as the number of leaves with
 *   non-zero weight, calculated based on differences between occurrences of "10" and "01" substrings in paths from root to leaf.
 *
 * Algorithms/Techniques:
 *   - Tree traversal and degree counting to identify leaves
 *   - Game theory (minimax) simulation using optimal play assumptions
 *   - String processing for path analysis and weight calculation
 *   - Greedy strategy handling for '?'
 *
 * Time Complexity: O(N) per test case, where N is the number of vertices.
 * Space Complexity: O(N), used for adjacency data structures and input storage.
 */

using System;
using System.Collections.Generic;
class Program {
  const int N = 114514;
  static int[] d = new int[N];
  static void Main(string[] args) {
    int T = int.Parse(Console.ReadLine());
    while (T-- > 0) {
      int n = int.Parse(Console.ReadLine());
      for (int i = 1; i <= n; i++)
        d[i] = 0;
      for (int i = 1; i < n; i++) {
        string[] edge = Console.ReadLine().Split();
        int u = int.Parse(edge[0]);
        int v = int.Parse(edge[1]);
        d[u]++;
        d[v]++;
      }
      string s = Console.ReadLine();
      int[] c = new int[3];
      int a2 = 0;
      for (int i = 2; i <= n; i++) {
        if (s[i - 1] == '?')
          a2++;
      }
      for (int i = 2; i <= n; i++) {
        if (d[i] == 1) { // Leaf node check
          if (s[i - 1] == '?')
            c[2]++;
          else
            c[s[i - 1] - '0']++;
        }
      }
      if (s[0] != '?') {
        // If root is fixed, compute based on the known value and how many '2' (unassigned) leaves there are
        Console.WriteLine(c[(s[0] - '0') ^ 1] + (c[2] + 1) / 2);
      } else if (c[0] != c[1]) {
        // If root is unknown, but existing known values differ, choose max
        Console.WriteLine(Math.Max(c[0], c[1]) + c[2] / 2);
      } else {
        // If both known values are equal, try greedy assignment
        Console.WriteLine(c[0] + (c[2] + (a2 - c[2]) % 2) / 2);
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/