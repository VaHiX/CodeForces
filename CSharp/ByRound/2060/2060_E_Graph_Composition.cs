// Problem: CF 2060 E - Graph Composition
// https://codeforces.com/contest/2060/problem/E

/*
 * Problem: Graph Composition
 * Purpose: Determine the minimum number of operations to make graph F structurally equivalent to graph G.
 * Algorithms:
 *   - DFS to find connected components in graph G
 *   - Identify bridges between components of G that are missing in F
 *   - Count extra components in F that need to be merged
 * Time Complexity: O(n + m1 + m2) where n is number of nodes, m1 and m2 are edges in F and G
 * Space Complexity: O(n + m1 + m2) for storing graphs and visited arrays
 */

using System;
using System.Collections.Generic;

public class ConnectivityTransformer {
  private List<int>[] graphF;        // Adjacency list for graph F
  private List<int>[] graphG;        // Adjacency list for graph G
  private bool[] visitedF;           // Visited array for DFS on F
  private bool[] visitedG;           // Visited array for DFS on G
  private int[] componentIdG;        // Component IDs of nodes in G
  private HashSet<(int, int)> blockedEdges; // Set to store edges from F that should be skipped during traversal
  private int nodeCount;             // Number of nodes

  public int MinOperations(int n, int[][] edgesF, int[][] edgesG) {
    nodeCount = n;
    graphF = new List<int>[n];
    graphG = new List<int>[n];
    visitedF = new bool[n];
    visitedG = new bool[n];
    componentIdG = new int[n];
    blockedEdges = new HashSet<(int, int)>();
    
    // Initialize adjacency lists
    for (int i = 0; i < n; i++) {
      graphF[i] = new List<int>();
      graphG[i] = new List<int>();
    }
    
    // Build graph F from input edges
    foreach (var edge in edgesF) {
      int u = edge[0] - 1;
      int v = edge[1] - 1;
      graphF[u].Add(v);
      graphF[v].Add(u);
    }
    
    // Build graph G from input edges
    foreach (var edge in edgesG) {
      int u = edge[0] - 1;
      int v = edge[1] - 1;
      graphG[u].Add(v);
      graphG[v].Add(u);
    }
    
    // Find connected components in G using DFS
    int componentCountG = 0;
    for (int i = 0; i < n; i++) {
      if (!visitedG[i]) {
        componentCountG++;
        DFS_G(i, componentCountG);
      }
    }
    
    // Count bridge edges between different components of G that are missing in F
    int bridgeCount = 0;
    for (int u = 0; u < n; u++) {
      foreach (int v in graphF[u]) {
        if (componentIdG[u] != componentIdG[v]) { // If nodes are in different components
          var edge = NormalizeEdge(u, v);
          if (!blockedEdges.Contains(edge)) {
            blockedEdges.Add(edge); // Mark this edge as processed
            bridgeCount++;
          }
        }
      }
    }
    
    // Count connected components in F using DFS
    int componentCountF = 0;
    for (int i = 0; i < n; i++) {
      if (!visitedF[i]) {
        componentCountF++;
        DFS_F(i);
      }
    }
    
    // Return total operations: bridges to add + components to merge
    return bridgeCount + (componentCountF - componentCountG);
  }
  
  // Helper method for DFS traversal on G to find connected components
  private void DFS_G(int u, int componentId) {
    visitedG[u] = true;
    componentIdG[u] = componentId;
    foreach (int v in graphG[u]) {
      if (!visitedG[v])
        DFS_G(v, componentId);
    }
  }
  
  // Helper method for DFS traversal on F to count components
  private void DFS_F(int u) {
    visitedF[u] = true;
    foreach (int v in graphF[u]) {
      var edge = NormalizeEdge(u, v);
      if (!visitedF[v] && !blockedEdges.Contains(edge)) {
        DFS_F(v);
      }
    }
  }
  
  // Normalize edge to ensure consistent ordering: smaller ID first
  private (int, int) NormalizeEdge(int u, int v) {
    return u < v ? (u, v) : (v, u);
  }
}

class Solution {
  static void Main() {
    var solver = new ConnectivityTransformer();
    int t = int.Parse(Console.ReadLine());
    List<int> res = new List<int>();
    while (t-- > 0) {
      string[] header = Console.ReadLine().Split(
          new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
      int n = int.Parse(header[0]);
      int m1 = int.Parse(header[1]);
      int m2 = int.Parse(header[2]);
      int[][] edgesF = new int [m1][];
      for (int i = 0; i < m1; i++) {
        string[] parts = Console.ReadLine().Split(
            new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
        edgesF[i] = new[] { int.Parse(parts[0]), int.Parse(parts[1]) };
      }
      int[][] edgesG = new int [m2][];
      for (int i = 0; i < m2; i++) {
        string[] parts = Console.ReadLine().Split(
            new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
        edgesG[i] = new[] { int.Parse(parts[0]), int.Parse(parts[1]) };
      }
      int result = solver.MinOperations(n, edgesF, edgesG);
      res.Add(result);
    }
    foreach (var i in res) {
      Console.WriteLine(i);
    }
  }
}


// https://github.com/VaHiX/codeForces/