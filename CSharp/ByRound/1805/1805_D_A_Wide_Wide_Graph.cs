// Problem: CF 1805 D - A Wide, Wide Graph
// https://codeforces.com/contest/1805/problem/D

/*
 * Problem: D. A Wide, Wide Graph
 * 
 * Purpose: 
 *   Given a tree with n vertices, for each k from 1 to n, compute the number of connected components
 *   in the graph G_k where two vertices are connected if their distance in the original tree is at least k.
 * 
 * Algorithms/Techniques:
 *   - Two BFS traversals to find the diameter of the tree
 *   - Sorting distances and using a two-pointer technique to count components efficiently
 * 
 * Time Complexity: O(n log n)
 *   - BFS traversals to compute distances: O(n)
 *   - Sorting the distances: O(n log n)
 *   - Processing for each k: O(n)
 * 
 * Space Complexity: O(n)
 *   - Storage for adjacency list, distance arrays, visited array: O(n)
 * 
 * Approach:
 *   1. Build adjacency list from input edges
 *   2. Perform two BFS traversals to find the diameter of the tree
 *   3. For each vertex, store the maximum distance to any leaf (i.e., the eccentricity)
 *   4. Sort these eccentricities
 *   5. Use a two-pointer approach to determine the number of connected components for each k
 */


using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int fyt = 1;
    List<string> output = new List<string>();
    for (int hz = 0; hz < fyt; hz++) {
      var n = int.Parse(Console.ReadLine());
      List<int> o = new List<int>();
      List<int>[] nodes = new List<int>[n];
      for (int i = 0; i < n - 1; i++) {
        var a =
            Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
        if (nodes[a[0] - 1] == null)
          nodes[a[0] - 1] = new List<int>();
        if (nodes[a[1] - 1] == null)
          nodes[a[1] - 1] = new List<int>();
        nodes[a[0] - 1].Add(a[1] - 1);
        nodes[a[1] - 1].Add(a[0] - 1);
      }
      bool[] visited = new bool[n];
      int[] distance = new int[n];
      Queue<int[]> q = new Queue<int[]>();
      q.Enqueue(new int[] { 0, 0 });
      while (q.Count > 0) {
        var d = q.Dequeue();
        visited[d[0]] = true;
        int v = d[1];
        distance[d[0]] = v;
        nodes[d[0]]
            .Where(i => !visited[i])
            .ToList()
            .ForEach(i => q.Enqueue(new int[2] { i, v + 1 }));
      }
      int md = distance.Max();
      int d1 = Array.IndexOf(distance, md);
      visited = new bool[n];
      distance = new int[n];
      q = new Queue<int[]>();
      q.Enqueue(new int[] { d1, 0 });
      while (q.Count > 0) {
        var d = q.Dequeue();
        visited[d[0]] = true;
        int v = d[1];
        distance[d[0]] = v;
        nodes[d[0]]
            .Where(i => !visited[i])
            .ToList()
            .ForEach(i => q.Enqueue(new int[2] { i, v + 1 }));
      }
      md = distance.Max();
      int d2 = Array.IndexOf(distance, md);
      visited = new bool[n];
      var distance2 = new int[n];
      q = new Queue<int[]>();
      q.Enqueue(new int[] { d2, 0 });
      while (q.Count > 0) {
        var d = q.Dequeue();
        visited[d[0]] = true;
        int v = d[1];
        distance2[d[0]] = v;
        nodes[d[0]]
            .Where(i => !visited[i])
            .ToList()
            .ForEach(i => q.Enqueue(new int[2] { i, v + 1 }));
      }
      for (int i = 0; i < n; i++) {
        distance[i] = Math.Max(distance[i], distance2[i]);
      }
      Array.Sort(distance);
      int l = 0;
      int cm = 1;
      for (int k = 1; k <= n && l < n; k++) {
        if (k <= distance[l]) {
          o.Add(cm);
        } else {
          cm++;
          l++;
          k--; // Adjust k as we may have skipped some values
        }
      }
      for (int k = o.Count; k < n; k++) {
        o.Add(n);
      }
      output.Add(string.Join(" ", o));
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/