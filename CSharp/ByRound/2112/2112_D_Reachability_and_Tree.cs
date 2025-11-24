// Problem: CF 2112 D - Reachability and Tree
// https://codeforces.com/contest/2112/problem/D

/*
 * Problem: D. Reachability and Tree
 *
 * Purpose: Given an undirected tree with n vertices, determine if we can assign directions to each edge such that exactly n ordered pairs (u,v) exist where there is a directed path from u to v.
 *
 * Algorithm:
 * - Identify a node with degree 2; this becomes the "pivot" point for the DFS traversal
 * - Direct edges away from pivot in one branch and towards pivot in another branch
 * - Perform DFS to traverse all remaining nodes and direct their edges accordingly
 * - For valid trees, this ensures exactly n good pairs
 *
 * Time Complexity: O(n) per test case — each node and edge is visited once.
 * Space Complexity: O(n) — for storing adjacency list, used array, and stack.
 */

using System;
using System.Collections.Generic;
class Solution {
  static void Main() {
    long t = long.Parse(Console.ReadLine());
    while (t-- > 0) {
      long n = long.Parse(Console.ReadLine());
      var g = new List<Tuple<long, int>>[n + 1];
      for (int i = 1; i <= n; i++)
        g[i] = new List<Tuple<long, int>>(); // Initialize adjacency list
      for (int e = 0; e < n - 1; e++) {
        var input = Console.ReadLine().Split();
        long u = long.Parse(input[0]);
        long v = long.Parse(input[1]);
        g[u].Add(Tuple.Create(v, e)); // Add edge with id 'e'
        g[v].Add(Tuple.Create(u, e));
      }
      long pvt = -1;
      for (long i = 1; i <= n; i++) {
        if (g[i].Count == 2) { // Find a pivot node with degree 2
          pvt = i;
          break;
        }
      }
      if (pvt == -1) {
        Console.WriteLine("NO"); // No valid pivot, impossible to direct edges
        continue;
      }
      long a = g[pvt][0].Item1; // First neighbor of pivot
      int idA = g[pvt][0].Item2; // Edge ID to first neighbor
      long b = g[pvt][1].Item1; // Second neighbor of pivot
      int idB = g[pvt][1].Item2; // Edge ID to second neighbor
      var used = new bool[n]; // Track which edges are directed
      used[idA] = used[idB] = true;
      var res = new List<Tuple<long, long>>(); // Store result directed edges
      res.Add(Tuple.Create(a, pvt)); // Direct edge from a to pivot
      res.Add(Tuple.Create(pvt, b)); // Direct edge from pivot to b
      var stk = new Stack<Tuple<long, long, bool>>(); // Stack for DFS: (current node, parent, direction flag)
      stk.Push(Tuple.Create(a, pvt, true));  // Start traversal with one branch
      stk.Push(Tuple.Create(b, pvt, false)); // Start traversal with other branch
      while (stk.Count > 0) {
        var curr = stk.Pop();
        long u = curr.Item1, pr = curr.Item2;
        bool dir = curr.Item3;
        foreach (var edge in g[u]) {
          long v = edge.Item1;
          int id = edge.Item2;
          if (used[id]) // Skip already used edges
            continue;
          used[id] = true;
          if (dir) { // If traversal is from parent to current node
            res.Add(Tuple.Create(u, v)); // Direct edge u -> v
            stk.Push(Tuple.Create(v, u, false));
          } else { // Else direct from child to parent
            res.Add(Tuple.Create(v, u)); // Direct edge v -> u
            stk.Push(Tuple.Create(v, u, true));
          }
        }
      }
      Console.WriteLine("YES");
      foreach (var pair in res) {
        Console.WriteLine($"{pair.Item1} {pair.Item2}");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/