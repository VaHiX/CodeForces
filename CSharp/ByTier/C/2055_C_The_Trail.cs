// Problem: CF 2055 C - The Trail
// https://codeforces.com/contest/2055/problem/C

/*
Purpose: 
This program solves the problem of restoring a tampered mountainous terrain grid where a path from (1,1) to (n,m) has been cleared (altitude set to 0). 
The goal is to assign altitudes to the cleared path cells such that all rows and columns have equal sums.

Algorithms/Techniques:
- Graph-based approach with BFS to solve a system of linear equations derived from row/column sum constraints
- The path is modeled as a graph where rows and columns are nodes, and path edges connect them
- BFS is used to process nodes with degree 1, propagating values along the path
- The solution uses a topological-like BFS for consistent assignment

Time Complexity: O(n * m)
Space Complexity: O(n * m)
*/
using System;
using System.Collections.Generic;
class Program {
  static void EnqueueAndMark(int node, Queue<int> queue, bool[] inQueue) {
    queue.Enqueue(node);
    inQueue[node] = true;
  }
  static void AssignGridValue(int x, int y, long val, long[,] grid) {
    grid[x, y] = val;
  }
  static void ApplyEdgeChanges(int eid, int u, int nei, long[] eVal,
                               bool[] usedE, bool[] rm, int[] deg, long[] B) {
    eVal[eid] = B[u]; // Assign value from node u to edge
    usedE[eid] = true; // Mark edge as used
    rm[u] = true; // Mark node u as removed
    deg[u]--; // Decrease degree of node u
    deg[nei]--; // Decrease degree of neighbor node
    B[nei] -= eVal[eid]; // Propagate the value to neighbor node
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var nm = Console.ReadLine().Split();
      int n = int.Parse(nm[0]);
      int m = int.Parse(nm[1]);
      string s = Console.ReadLine();
      int L = n + m - 1; // Length of the path
      var pth = new List<Tuple<int, int>>(); // Stores coordinates of path
      int r = 0, c = 0;
      pth.Add(new Tuple<int, int>(r, c)); // Start at (0,0)
      foreach (var ch in s) {
        var move = new Dictionary<char, Action> { { 'D', () => r++ },
                                                  { 'R', () => c++ } };
        if (move.ContainsKey(ch))
          move[ch].Invoke(); // Move step by step along the path
        pth.Add(new Tuple<int, int>(r, c));
      }
      var grd = new long[n, m]; // Original grid
      var onPth = new bool[n, m]; // Boolean grid marking path cells
      foreach (var p in pth)
        onPth[p.Item1, p.Item2] = true; // Mark path cells
      for (int i = 0; i < n; i++) {
        var row = Console.ReadLine().Split();
        for (int j = 0; j < m; j++) {
          grd[i, j] = long.Parse(row[j]);
        }
      }
      // Compute the sum of non-path cells for each row and column
      var rowSum = new long[n];
      var colSum = new long[m];
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          rowSum[i] += !onPth[i, j] ? grd[i, j] : 0;
          colSum[j] += !onPth[i, j] ? grd[i, j] : 0;
        }
      }
      // Build a graph for BFS processing
      int V = n + m; // Nodes: n rows + m columns
      var B = new long[V]; // Target sums for each row/column
      int idx = 0;
      foreach (var value in rowSum)
        B[idx++] = -value; // Negative because we are solving for deficit
      idx = 0;
      foreach (var value in colSum)
        B[n + idx++] = -value;
      int E = L; // Number of edges = length of path
      var adj = new List<Tuple<int, int>>[V]; // Adjacency list for graph
      for (int i = 0; i < V; i++)
        adj[i] = new List<Tuple<int, int>>();
      // Build graph with edges connecting row nodes to column nodes in path
      for (int i = 0; i < L; i++) {
        int u = pth[i].Item1; // Row node
        int v = pth[i].Item2 + n; // Column node (shifted by n)
        adj[u].Add(Tuple.Create(v, i)); // Add edge to column node
        adj[v].Add(Tuple.Create(u, i)); // Add edge to row node
      }
      var deg = new int[V]; // Degree of each node
      for (int i = 0; i < V; i++) {
        deg[i] = adj[i].Count;
      }
      bool[] usedE = new bool[E]; // Track used edges
      long[] eVal = new long[E]; // Value assigned to each edge
      Queue<int> q = new Queue<int>(); // BFS queue
      bool[] inQ = new bool[V]; // Track which nodes are in queue
      bool[] rm = new bool[V]; // Track which nodes are removed
      // Initialize the queue with nodes of degree 1
      for (int i = 0; i < V; i++) {
        var actions = new Dictionary<int, Action> { { 1, () => {
                                                       q.Enqueue(i);
                                                       inQ[i] = true;
                                                     } } };
        if (deg[i] == 1)
          actions[1](); // Add degree 1 nodes to queue
      }
      // Begin BFS processing to calculate edge values
      while (q.Count > 0) {
        int u = q.Dequeue();
        bool shouldContinue = rm[u] || deg[u] == 0;
        if (shouldContinue)
          continue;
        int nei = -1, eid = -1;
        foreach (var p in adj[u]) {
          switch (usedE[p.Item2]) {
          case false:
            nei = p.Item1; // Get neighbor node
            eid = p.Item2; // Get edge ID
            break;
          }
        }
        switch (eid) {
        case -1:
          continue; // No valid edge found
        }
        ApplyEdgeChanges(eid, u, nei, eVal, usedE, rm, deg, B); // Process edge
        // Add neighbor to queue if it becomes degree 1 and not in queue
        bool canProcess = (deg[nei] == 1) ? (!rm[nei] && !inQ[nei]) : false;
        if (canProcess) {
          EnqueueAndMark(nei, q, inQ);
        }
      }
      // Assign final values to the path cells in the grid
      for (int i = 0; i < L; i++) {
        AssignGridValue(pth[i].Item1, pth[i].Item2, eVal[i], grd); // Assign values to path
      }
      // Output the restored grid
      for (int i = 0; i < n; i++) {
        long[] row = new long[m];
        for (int j = 0; j < m; j++) {
          row[j] = grd[i, j];
        }
        Console.WriteLine(string.Join(" ", row));
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/