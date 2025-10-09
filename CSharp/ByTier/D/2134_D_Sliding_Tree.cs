// Problem: CF 2134 D - Sliding Tree
// https://codeforces.com/contest/2134/problem/D

/*
 * Problem: D. Sliding Tree
 * Purpose: Transform a tree into a path graph using sliding operations.
 * Algorithm:
 *   - Identify the vertex with maximum degree (likely center of tree).
 *   - If max degree > 2, perform DFS-based computations to find optimal sliding operation.
 *   - Otherwise, tree is already a path, return -1.
 *
 * Time Complexity: O(n) per test case, since each node visited at most twice in DFS.
 * Space Complexity: O(n) for adjacency list and auxiliary arrays.
 */

using System.Text;
namespace SlidingTree;
class Program {
  static void Solve() {
    int n = Next(); // Read number of nodes
    nn = new List<int>[n]; // Initialize adjacency list
    for (int i = 0; i < n; i++)
      nn[i] = new(); // Each node has an empty neighbor list initially
    for (int i = 1; i < n; i++) {
      int a = Next() - 1; // Read edge endpoint a and convert to 0-based indexing
      int b = Next() - 1; // Read edge endpoint b and convert to 0-based indexing
      nn[a].Add(b); // Add edge from a to b
      nn[b].Add(a); // Add edge from b to a (undirected)
    }
    int max = 0;
    for (int i = 0; i < n; i++)
      if (nn[max].Count < nn[i].Count) // Find node with maximum degree
        max = i;
    if (nn[max].Count > 2) { // If max degree > 2, tree isn't a path
      int[] d1 = new int[n]; // Distance from farthest leaf to each node using first DFS
      int[] d2 = new int[n]; // Distance from root to each node using second DFS
      for (int i = 0; i < n; i++)
        if (nn[i].Count == 1) { // Find a leaf node
          max = i;
          break;
        }
      Dfs2(max, max, d2); // Start second DFS from that leaf
      max = 0;
      for (int i = 0; i < n; i++)
        if (d2[max] < d2[i]) // Find the farthest node from root of first DFS
          max = i;
      Dfs1(max, max, d1); // First DFS to compute distances in tree
      int prev = max;
      while (nn[max].Count < 3) { // Move up until we reach a node with degree > 2
        int next = -1;
        foreach (var j in nn[max]) {
          if (d1[max] > d1[j]) { // Look for next node with larger distance
            if (next == -1 || d1[next] < d1[j]) // Update if better
              next = j;
          }
        }
        prev = max;
        max = next;
      }
      {
        int next = -1;
        foreach (var j in nn[max]) {
          if (next == -1 || d1[next] > d1[j]) // Find the node with smallest distance to leaf
            next = j;
        }
        writer.WriteLine($"{prev + 1} {max + 1} {next + 1}"); // Output sliding operation
      }
      return;
    }
    writer.WriteLine("-1"); // If max degree <= 2, already a path
  }
  static List<int>[] nn; // Global adjacency list representing tree

  // Compute distances from root to all other nodes using DFS
  static void Dfs1(int to, int from, int[] d) {
    d[to] = 1;
    foreach (var j in nn[to]) {
      if (j == from)
        continue;
      Dfs1(j, to, d);
      d[to] = Math.Max(d[to], 1 + d[j]); // Update distance to be maximum of current and child's
    }
  }

  // Computes depth of each node from given root using recursive DFS
  static void Dfs2(int to, int from, int[] d) {
    d[to] = 1 + d[from]; // Set distance as parent distance + 1
    foreach (var j in nn[to]) {
      if (j == from)
        continue;
      Dfs2(j, to, d); // Continue DFS on child node
    }
  }

  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      Solve(); // Process each case
    writer.Flush();
  }

  static int Next() { // Helper to parse integer input
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1; // Handle negative integer
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