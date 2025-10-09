// Problem: CF 2071 C - Trapmigiano Reggiano
// https://codeforces.com/contest/2071/problem/C

/*
 * Problem: Trapmigiano Reggiano
 * Purpose: Given a tree, find a permutation of vertices such that a mouse starting at 'st' 
 *          will inevitably end up at 'en' after visiting all vertices in the order specified.
 *          At each step, the mouse moves towards the vertex where cheese appears, unless it's already there.
 * 
 * Algorithms/Techniques:
 *  - Build a tree from input edges
 *  - Compute distances from 'en' using DFS (distance to trap)
 *  - Sort vertices in descending order of distance from 'en'
 *  - Output this sorted list as the permutation
 * 
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing tree, distances, and permutation.
 */

using System;
using System.Collections.Generic;
using System.Linq;

class PerfectPermutation {
  // Depth First Search to compute distances from a node to all other nodes
  static void DFS(int node, int parent, List<List<int>> tree, int[] dist) {
    foreach (int neighbor in tree[node]) {
      if (neighbor != parent) {           // Avoid going back to parent
        dist[neighbor] = dist[node] + 1;   // Set distance as parent's distance + 1
        DFS(neighbor, node, tree, dist);   // Recursively process neighbor
      }
    }
  }

  static void Solve() {
    string[] inputs = Console.ReadLine().Split();
    int n = int.Parse(inputs[0]);
    int st = int.Parse(inputs[1]);
    int en = int.Parse(inputs[2]);

    // Initialize adjacency list for tree
    List<List<int>> tree = new List<List<int>>(new List<int>[n + 1]);
    for (int i = 0; i <= n; i++)
      tree[i] = new List<int>();

    // Read edges and populate the tree
    for (int i = 0; i < n - 1; i++) {
      inputs = Console.ReadLine().Split();
      int u = int.Parse(inputs[0]);
      int v = int.Parse(inputs[1]);
      tree[u].Add(v);
      tree[v].Add(u);
    }

    // Compute distances from 'en' to each node
    int[] dist = Enumerable.Repeat(-1, n + 1).ToArray();
    dist[en] = 0;
    DFS(en, -1, tree, dist);

    // Generate a permutation sorted by decreasing distance from 'en'
    List<int> perm = Enumerable.Range(1, n).ToList();
    perm.Sort((a, b) => dist[b].CompareTo(dist[a]));

    // If start node is unreachable from end (distance remains -1), no solution
    if (dist[st] == -1) {
      Console.WriteLine("-1");
    } else {
      Console.WriteLine(string.Join(" ", perm));
    }
  }

  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0)
      Solve();
  }
}


// https://github.com/VaHiX/codeForces/