// Problem: CF 2107 D - Apple Tree Traversing
// https://codeforces.com/contest/2107/problem/D

/*
 * Problem: D. Apple Tree Traversing
 * 
 * Purpose:
 *   This code solves the problem of traversing a tree to find the lexicographically
 *   largest sequence of apple paths. Each path chosen must have apples on all nodes
 *   in it. The goal is to maximize the output sequence lexicographically.
 *
 * Algorithms/Techniques:
 *   - BFS traversal to find diameters of connected components.
 *   - Greedy selection of paths with maximum depth first.
 *   - Tree diameter calculation using two BFS traversals.
 *   - Sorting final results to ensure lexicographical order.
 *
 * Time Complexity:
 *   O(n^2) in worst case due to nested operations, but with optimizations,
 *   each node is processed at most twice for path selection in a component.
 *   Since sum of n over all test cases is bounded (1.5e5), it's efficient enough.
 *
 * Space Complexity:
 *   O(n) - for storing adjacency list and auxiliary arrays (visited, parent, depth, queue).
 */

using System;
using System.Collections.Generic;
using System.Text;

class Program {
  static int n;
  static List<int>[] g;
  static bool[] used;
  static int[] parent;
  static int[] depth;
  static int[] q;

  // Performs BFS from node s to find the farthest node and its depth.
  // Returns a tuple of (depth, leaf node).
  static (int len, int leaf) Bfs(int s) {
    int head = 0, tail = 0;
    q[tail++] = s;
    parent[s] = -1;
    depth[s] = 0;
    int bestLeaf = s, bestDepth = 0;
    while (head < tail) {
      int u = q[head++];
      int du = depth[u];
      if (du > bestDepth || (du == bestDepth && u > bestLeaf)) {
        bestDepth = du;
        bestLeaf = u;
      }
      foreach (var v in g[u])
        if (!used[v] && v != parent[u]) {   // Skip used nodes and parent to avoid going back
          parent[v] = u;
          depth[v] = du + 1;
          q[tail++] = v;
        }
    }
    return (bestDepth + 1, bestLeaf);
  }

  static void Main() {
    var sb = new StringBuilder();
    int T = int.Parse(Console.ReadLine());
    while (T-- > 0) {
      n = int.Parse(Console.ReadLine());
      g = new List<int>[n + 1];
      used = new bool[n + 1];
      parent = new int[n + 1];
      depth = new int[n + 1];
      q = new int[n + 1];
      for (int i = 1; i <= n; i++)
        g[i] = new List<int>();
      for (int i = 1; i < n; i++) {
        var p = Console.ReadLine().Split();
        int u = int.Parse(p[0]), v = int.Parse(p[1]);
        g[u].Add(v);
        g[v].Add(u);
      }
      var ans = new List<(int d, int y, int z)>();
      int nextStart = 1;
      while (true) {
        while (nextStart <= n && used[nextStart])
          nextStart++;
        if (nextStart > n)
          break;
        var first = Bfs(nextStart);     // Find the farthest leaf in current component
        var second = Bfs(first.leaf);   // From that leaf, find another farthest node
        int j = first.leaf, k = second.leaf, d = second.len;
        ans.Add((d, Math.Max(j, k), Math.Min(j, k)));  // Store result with max/min ordering
        for (int cur = k; cur != -1; cur = parent[cur])  // Mark all nodes in path as used
          used[cur] = true;
      }
      ans.Sort((a, b) => {
        int c = b.d.CompareTo(a.d);       // Sort by depth descending
        if (c != 0)
          return c;
        c = b.y.CompareTo(a.y);           // If depths equal, sort by y descending
        if (c != 0)
          return c;
        return b.z.CompareTo(a.z);        // If both equal, sort by z descending
      });
      sb.Clear();
      foreach (var t in ans)
        sb.Append(t.d).Append(' ').Append(t.y).Append(' ').Append(t.z).Append(' ');
      Console.WriteLine(sb.ToString().Trim());
    }
  }
}


// https://github.com/VaHiX/CodeForces/