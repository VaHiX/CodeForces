// Problem: CF 2117 F - Wildflower
// https://codeforces.com/contest/2117/problem/F

/*
F. Wildflower
Purpose: Count the number of ways to assign values 1 or 2 to each vertex of a tree such that all subtree sums are unique.
Approach:
- For each tree, determine if it's possible to make all subtree sums distinct.
- If there are more than 2 leaves, no solution exists (output 0).
- If there is exactly one leaf, all assignments work (output 2^n).
- Otherwise, identify a node with two children and compute the number of valid assignments using dynamic programming and combinatorics.
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing tree structure and auxiliary arrays
*/

using System;
using System.Collections.Generic;
class Program {
  const long MOD = 1_000_000_007;
  
  // Fast exponentiation with modulo
  static long Pow2(long x) {
    long res = 1, a = 2;
    while (x > 0) {
      if ((x & 1) == 1)
        res = res * a % MOD;
      a = a * a % MOD;
      x >>= 1;
    }
    return res;
  }
  
  static void Main() {
    int T = int.Parse(Console.ReadLine());
    while (T-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var g = new List<int>[n + 1];
      for (int i = 0; i <= n; i++)
        g[i] = new List<int>();
      for (int i = 0; i < n - 1; ++i) {
        var parts = Console.ReadLine().Split();
        int u = int.Parse(parts[0]);
        int v = int.Parse(parts[1]);
        g[u].Add(v);
        g[v].Add(u);
      }
      
      // Build parent and child arrays for the rooted tree
      var parent = new int[n + 1];
      var child = new List<int>[n + 1];
      for (int i = 0; i <= n; i++)
        child[i] = new List<int>();
      var st = new Stack<int>();
      st.Push(1); // Root is 1
      parent[1] = -1;
      while (st.Count > 0) {
        int u = st.Pop();
        foreach (int v in g[u]) {
          if (v != parent[u]) {
            parent[v] = u;
            child[u].Add(v);
            st.Push(v);
          }
        }
      }
      
      // Find all leaves
      var leaves = new List<int>();
      for (int v = 1; v <= n; ++v)
        if (child[v].Count == 0)
          leaves.Add(v);
      
      // If more than two leaves exist, impossible to satisfy unique sums
      if (leaves.Count > 2) {
        Console.WriteLine(0);
        continue;
      }
      
      // If only one leaf, all assignments valid
      if (leaves.Count == 1) {
        Console.WriteLine(Pow2(n));
        continue;
      }
      
      // Find node with exactly two children
      int B = -1;
      for (int v = 1; v <= n; ++v) {
        if (child[v].Count == 2) {
          B = v;
          break;
        }
      }
      
      int c1 = child[B][0], c2 = child[B][1];
      
      // Function to compute subtree size
      Func<int, long> SubtreeSize = root => {
        long sz = 0;
        var s = new Stack<int>();
        s.Push(root);
        while (s.Count > 0) {
          int u = s.Pop();
          sz++;
          foreach (int v in child[u])
            s.Push(v);
        }
        return sz;
      };
      
      long sz1 = SubtreeSize(c1);
      long sz2 = SubtreeSize(c2);
      long d = Math.Abs(sz1 - sz2);
      long t = n - sz1 - sz2;
      
      // Compute contribution factor (F)
      long F = (d == 0) ? 2L : (3L * Pow2(d - 1)) % MOD;
      long ans = Pow2(t) * F % MOD;
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/