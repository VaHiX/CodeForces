// Problem: CF 2065 F - Skibidus and Slay
// https://codeforces.com/contest/2065/problem/F

/*
 * Problem: F. Skibidus and Slay
 * 
 * Purpose: Given a tree with integers on each vertex, determine for each integer value
 *          whether there exists a non-trivial simple path where that value is the majority.
 *          A majority value appears strictly more than floor(k/2) times in a path of k vertices.
 * 
 * Algorithm/Techniques:
 * - For each value x, check if it can be majority in any path:
 *   - If frequency of x is less than 2, it cannot be majority (since path must have at least 2 nodes).
 *   - Check edges: if two adjacent nodes have same value, that value can be majority in a path of length 2.
 *   - For each node u, check its neighbors and see if any neighbor value appears at least twice among neighbors,
 *     then that value can be majority in some path.
 * 
 * Time Complexity: O(n^2) worst case, but in practice much better due to optimizations.
 * Space Complexity: O(n)
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    StringBuilder sb = new StringBuilder();
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] vals = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int[] freq = new int[n + 1];
      for (int i = 0; i < n; i++)
        freq[vals[i]]++;
      List<int>[] adj = new List<int>[n];
      for (int i = 0; i < n; i++)
        adj[i] = new List<int>();
      for (int i = 0; i < n - 1; i++) {
        var parts = Console.ReadLine().Split();
        int u = int.Parse(parts[0]) - 1, v = int.Parse(parts[1]) - 1;
        adj[u].Add(v);
        adj[v].Add(u);
      }
      bool[] valid = new bool[n + 1];
      // Initialize valid array: if frequency of value is less than 2, cannot be majority
      for (int x = 1; x <= n; x++) {
        if (freq[x] < 2)
          valid[x] = false;
      }
      // Check for paths of length 2 (two adjacent nodes)
      for (int u = 0; u < n; u++) {
        foreach (var v in adj[u]) {
          if (u < v && vals[u] == vals[v])
            valid[vals[u]] = true;
        }
      }
      // Check for longer paths by examining neighbors of each node
      for (int u = 0; u < n; u++) {
        Dictionary<int, int> dic = new Dictionary<int, int>();
        foreach (var v in adj[u]) {
          int x = vals[v];
          if (!dic.ContainsKey(x))
            dic[x] = 0;
          dic[x]++;
        }
        foreach (var kv in dic) {
          if (kv.Value >= 2)
            valid[kv.Key] = true;
        }
      }
      // Generate output string
      for (int i = 1; i <= n; i++) {
        sb.Append(valid[i] ? '1' : '0');
      }
      sb.AppendLine();
    }
    Console.Write(sb.ToString());
  }
}


// https://github.com/VaHiX/CodeForces/