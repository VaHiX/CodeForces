// Problem: CF 2131 D - Arboris Contractio
// https://codeforces.com/contest/2131/problem/D

/*
 * Problem: D. Arboris Contractio
 * Purpose: Given a tree, find the minimum number of operations to minimize its diameter.
 *          Each operation allows choosing two vertices s and t, removing the path between them,
 *          and connecting all nodes on that path directly to s.
 *          
 * Algorithms Used:
 *   - Tree DFS traversal with subtree computations
 *   - Dynamic programming on trees to compute required operations at each node
 *   - Diameter minimization via strategic operation selection
 *
 * Time Complexity: O(n) per test case, where n is the number of vertices.
 * Space Complexity: O(n) for storing graph and auxiliary arrays.
 */

using System;
using System.Collections.Generic;
using System.Linq;

class Program {
  static void Solve() {
    int n = int.Parse(Console.ReadLine()); // Read number of vertices
    var graph = new List<int>[n + 1]; // Adjacency list representation of the tree
    var degree = new int[n + 1]; // Degree of each vertex
    for (int i = 0; i <= n; i++)
      graph[i] = new List<int>();
    for (int i = 0; i < n - 1; i++) { // Read edges and build the tree
      var parts = Console.ReadLine().Split();
      int u = int.Parse(parts[0]);
      int v = int.Parse(parts[1]);
      graph[u].Add(v);
      graph[v].Add(u);
      degree[u]++;
      degree[v]++;
    }
    if (degree.Any(d => d == n - 1)) { // If there's a vertex connected to all others, diameter is already minimized
      Console.WriteLine(0);
      return;
    }
    var subtreeSize = new int[n + 1]; // Size of subtree rooted at each node
    var leafCountInSubtree = new int[n + 1]; // Number of leaves in the subtree rooted at each node
    var operationsRequired = new long[n + 1]; // Minimum operations required for subtree rooted at each node
    
    void Dfs(int node, int parent) { // DFS to calculate subtree information
      subtreeSize[node] = 1;
      leafCountInSubtree[node] = (degree[node] == 1) ? 1 : 0; // If leaf, count it as one leaf
      operationsRequired[node] = 0;
      foreach (var neighbor in graph[node]) {
        if (neighbor == parent)
          continue;
        Dfs(neighbor, node); // Recursively process children
        subtreeSize[node] += subtreeSize[neighbor];
        leafCountInSubtree[node] += leafCountInSubtree[neighbor];
        if (subtreeSize[neighbor] > 1) {
          operationsRequired[node] += leafCountInSubtree[neighbor]; // Count required operations for child's subtree
        }
      }
    }
    Dfs(1, 0); // Start DFS from node 1
    
    long totalLeaves = leafCountInSubtree[1];
    long minOps = long.MaxValue;
    
    for (int node = 1; node <= n; node++) { // Try each node as candidate root
      long currentOps = operationsRequired[node];
      if (node != 1) { // If not the initial root, also consider parent's side
        int parentSideSize = n - subtreeSize[node];
        if (parentSideSize > 1) {
          currentOps += (totalLeaves - leafCountInSubtree[node]); // Add cost of operations on parent side
        }
      }
      if (currentOps < minOps)
        minOps = currentOps;
    }
    Console.WriteLine(minOps);
  }

  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      Solve(); // Process each test case
    }
  }
}


// https://github.com/VaHiX/codeForces/