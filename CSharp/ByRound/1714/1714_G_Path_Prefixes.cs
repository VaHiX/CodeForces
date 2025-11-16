// Problem: CF 1714 G - Path Prefixes
// https://codeforces.com/contest/1714/problem/G

// Algorithm: DFS traversal of tree with binary search for maximum valid prefix
// Time Complexity: O(n log n) per test case due to binary search on path prefixes
// Space Complexity: O(n) for storing tree structure, path data, and auxiliary arrays

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
namespace Compete2 {
partial class MainClass {
  public static List<long> b = new List<long>();  // Stores cumulative b_j values along the path
  public static List<int> path = new List<int>(); // Not directly used in final logic, but maintains path structure
  public static long[] a; // Stores cumulative a_j values along the path
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine());
      List<int> o = new List<int>(); // Stores results for each node
      List<int>[] children = new List<int>[n]; // Adjacency list for tree structure
      o.Add(0); // Placeholder for root node (not used in output)
      children[0] = new List<int>();
      int[] parent = new int[n]; // Parent of each node
      int[] a1 = new int[n]; // Original a_j values for each edge
      int[] b1 = new int[n]; // Original b_j values for each edge
      b = new List<long>(); // Cumulative b_j values
      a = new long[n]; // Cumulative a_j values
      for (int i = 1; i < n; i++) {
        children[i] = new List<int>();
        o.Add(0);
      }
      for (int i = 1; i < n; i++) {
        var c = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
        parent[i] = c[0] - 1;
        children[c[0] - 1].Add(i);
        a1[i] = c[1];
        b1[i] = c[2];
      }
      Stack<int[]> dfs = new Stack<int[]>(); // DFS stack to traverse tree
      dfs.Push(new int[2] { 0, 0 }); // Start DFS from root node 0, initial path depth 0
      while (dfs.Count > 0) {
        int[] node2 = dfs.Pop(); // Current node and depth in path
        int node = node2[0];
        if (node != 0)
          a[node] = a1[node] + a[parent[node]]; // Compute cumulative a_j for current node
        // Clean up b list to maintain only path from root to current node
        for (int i = b.Count - 1; i >= node2[1]; i--)
          b.RemoveAt(i);
        // Update cumulative b_j for current node
        if (b.Count > 0)
          b.Add(b1[node] + b.Last());
        else
          b.Add(b1[node]);
        long s = a[node]; // Cumulative a_j up to current node
        int l = 0;
        int r = b.Count - 1;
        // Check if entire path is valid (b_sum <= a_sum)
        if (b.Last() <= s)
          o[node] = b.Count - 1;
        else {
          // Binary search for the maximum index such that b_sum <= a_sum
          while (r - l > 1) {
            int m = (r + l) / 2;
            if (b[m] <= s) {
              l = m;
            } else
              r = m;
          }
          // Final check after binary search
          if (r != l) {
            if (b[r] <= s)
              l = r;
          }
          o[node] = l; // Store result for current node
        }
        // Add children to DFS stack for further traversal
        children[node].ForEach(w => dfs.Push(new int[2] { w, node2[1] + 1 }));
      }
      o.RemoveAt(0); // Remove placeholder result for root node
      output.Add(string.Join(" ", o)); // Add results for current test case to output
    }
    output.ForEach(d => Console.WriteLine(d)); // Print all results
  }
}
}


// https://github.com/VaHiX/CodeForces/