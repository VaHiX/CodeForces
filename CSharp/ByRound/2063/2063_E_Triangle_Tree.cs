// Problem: CF 2063 E - Triangle Tree
// https://codeforces.com/contest/2063/problem/E

// Flowerbox:
// Problem: E. Triangle Tree
// Description: Given a tree with n vertices, compute the sum of f(i,j) over all pairs (i,j) where i < j.
//              f(i,j) is defined as the number of distinct integer values x such that there exists a 
//              non-degenerate triangle with side lengths dist(i,lca(i,j)), dist(j,lca(i,j)), and x.
//              If (i,j) is not a good pair, then f(i,j) = 0.
//
// Approach:
// 1. Use DFS to compute subtree sizes and depths of nodes.
// 2. For each node, evaluate contributions to answer based on the number of good pairs.
// 3. Use careful bookkeeping of counts to efficiently compute triangle constraints using the formula for valid x values.
//
// Time Complexity: O(n) per test case
// Space Complexity: O(n) per test case

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var adj = new List<int>[n];
      for (int i = 0; i < n; i++)
        adj[i] = new List<int>();
      for (int i = 1; i < n; i++) {
        var edge = Console.ReadLine().Split().Select(int.Parse).ToArray();
        int u = edge[0] - 1;
        int v = edge[1] - 1;
        adj[u].Add(v);
        adj[v].Add(u);
      }
      var d = new long[n];       // depths of nodes
      var s = new long[n];       // sizes of subtrees
      var dc = new long[n];      // count of nodes at depth i
      var dcs = new long[n];     // suffix sum of dc array, used in computation
      
      // First DFS to compute subtree sizes and depths
      void Dfs1(int v, int p = -1) {
        dc[d[v]]++;   // increment count of nodes at current depth
        long sz = 1;  // initialize size with the node itself
        foreach (int w in adj[v]) {
          if (w != p) {
            d[w] = d[v] + 1;
            Dfs1(w, v);
            sz += s[w];   // accumulate subtree sizes
          }
        }
        s[v] = sz;    // store subtree size for current node
      }
      Dfs1(0);  // Start DFS from root (node 0)

      Array.Copy(dc, dcs, n);   // copy dc to dcs for suffix sum computation
      
      // Compute suffix sums for efficient traversal
      for (int i = n - 2; i >= 0; i--)
        dcs[i] += dcs[i + 1];

      long ans = 0, ans2 = 0;

      // Second DFS to compute final answer
      void Dfs2(int v, int p = -1) {
        // Contribution from pairs where one is in subtree and the other not
        ans += 2 * d[v] * (dcs[d[v]] - s[v]);

        long subcnt = s[v] - 1, lcnt = 0;
        foreach (int w in adj[v]) {
          if (w != p) {
            // Count pairs of nodes with one in subtree and one not
            lcnt += (subcnt - s[w]) * s[w];
            Dfs2(w, v);
          }
        }

        // Add contribution from pairs inside same subtree for good triangles
        ans2 += (2 * d[v] + 1) * (lcnt / 2);
      }

      Dfs2(0);  // Start second DFS from root

      // Final contribution due to self-pairs and valid triangle conditions
      for (int i = 0; i < n; i++) {
        ans2 += i * dc[i] * (dc[i] - 1);
      }

      Console.WriteLine(ans - ans2);
    }
  }
}


// https://github.com/VaHiX/codeForces/