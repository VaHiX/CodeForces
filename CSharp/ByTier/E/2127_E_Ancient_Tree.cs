// Problem: CF 2127 E - Ancient Tree
// https://codeforces.com/contest/2127/problem/E

﻿/*
E. Ancient Tree
Algorithm: 
  - Uses a tree DFS traversal to compute optimal coloring of vertices to minimize the sum of weights of "cutie" vertices.
  - A vertex v is cutie if there exist x, y such that lca(x, y) = v, c_x = c_y, and c_x != c_v.
  - For each node, we keep track of color sets from its children using a hashset for efficient intersection check.
  - Colors are assigned during DFS traversal to minimize the number of cutie vertices.
Time Complexity: O(n * k) per test case in average case due to hashset operations, where n is number of nodes and k is number of colors.
Space Complexity: O(n * k) for storing graph structure, color assignments, and intermediate hashsets during DFS.

*/

using System.Text;
namespace AncientTree;
class Program {
  static void Solve() {
    int n = Next();
    k = Next();
    w = new long[n];
    for (int i = 0; i < n; i++)
      w[i] = Next();
    c = new int[n];
    for (int i = 0; i < n; i++)
      c[i] = Next();
    nn = new List<int>[n];
    for (int i = 0; i < n; i++)
      nn[i] = new();
    for (int i = 1; i < n; i++) {
      int a = Next() - 1;
      int b = Next() - 1;
      nn[a].Add(b);
      nn[b].Add(a);
    }
    ans = 0;
    h = new HashSet<int>[n];
    Dfs(0, 0); // starts DFS from root (vertex 0)
    if (c[0] == 0) {
      Color(0, 0, 1); // assign color to root if needed
    }
    writer.WriteLine(ans);
    foreach (var i in c) {
      writer.Write(i);
      writer.Write(' ');
    }
    writer.WriteLine();
  }

  static void Color(int to, int from, int color) {
    c[to] = color;
    foreach (var j in nn[to]) {
      if (j == from)
        continue;
      Color(j, to, color); // Recursively color children
    }
  }

  static void Dfs(int to, int from) {
    // Base case - leaf node: recurse down to children
    foreach (var j in nn[to]) {
      if (j == from)
        continue;
      Dfs(j, to);
    }
    
    // Find the child with maximum number of distinct colors for optimization
    int max = -1;
    foreach (var j in nn[to]) {
      if (j == from)
        continue;
      if (max == -1 || h[max].Count < h[j].Count)
        max = j;
    }
    
    // Initialize the set of colors for current node
    if (max == -1) {
      h[to] = new();
      if (c[to] != 0)
        h[to].Add(c[to]);
      return;
    }
    
    // Copy the color set from the max child to current
    h[to] = h[max];
    
    // If current node has no assigned color, proceed with logic for determining its color
    if (h[to].Count == 0) {
      if (c[to] != 0) {
        h[to].Add(c[to]);
        Color(to, from, c[to]); // Color subtree of this node
      }
      return;
    }
    
    HashSet<int> cutie = new(); // track colors that would make parent a cutie
    foreach (var j in nn[to]) {
      if (j == from || j == max)
        continue;
      foreach (var y in h[j]) {
        if (!h[to].Add(y)) // Add color only if it's not already present, indicating a conflict
          cutie.Add(y);
      }
    }
    
    // Determine cost and coloring strategy based on number of conflicting colors
    if (cutie.Count > 1) {
      ans += w[to];
      if (c[to] == 0)
        c[to] = cutie.First(); // assign one conflicting color
    } else if (cutie.Count == 1) {
      if (c[to] == 0) {
        c[to] = cutie.First(); // assign the single conflicting color
      } else if (c[to] != cutie.First()) {
        ans += w[to]; // add cost because color conflicts with what was chosen for parent
      }
    } else {
      if (c[to] == 0)
        c[to] = h[to].First(); // assign any available color from subtree
    }

    h[to].Add(c[to]); // add current node's color to color set
    
    // Assign color to non-colored descendants using same chosen color as current node
    foreach (var j in nn[to]) {
      if (j == from)
        continue;
      if (c[j] == 0)
        Color(j, to, c[to]);
    }
  }

  static int k;
  static HashSet<int>[] h;
  static long ans;
  static long[] w;
  static int[] c;
  static List<int>[] nn;

  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      Solve();
    writer.Flush();
  }

  static int Next() {
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/