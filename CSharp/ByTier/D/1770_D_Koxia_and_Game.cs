// Problem: CF 1770 D - Koxia and Game
// https://codeforces.com/contest/1770/problem/D

/* 
 * Problem: Koxia and Game
 * 
 * Purpose: Determine the number of valid arrays c such that Koxia wins the game, 
 *          where Koxia and Mahiru play optimally. Koxia wins if the sequence d 
 *          (Mahiru's choices) is a permutation of integers from 1 to n.
 * 
 * Approach:
 * - For each round i, Koxia removes one element from {a[i], b[i], c[i]}, Mahiru 
 *   chooses one of the two remaining.
 * - Koxia wants the final sequence d to be a permutation of 1..n.
 * - Use a graph-based approach to analyze the constraints and compute valid c arrays.
 * 
 * Algorithms:
 * - Graph analysis using adjacency relationships.
 * - BFS approach to detect cycles/connected components.
 * - Modular arithmetic for large results.
 * 
 * Time Complexity: O(n log n) due to operations on SortedSet and HashSet.
 * Space Complexity: O(n) for storing data structures.
 */
using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var n = long.Parse(Console.ReadLine());
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 1;
      int[] ct = new int[n];
      Dictionary<long, HashSet<int>> ids = new Dictionary<long, HashSet<int>>();
      SortedSet<long> exclusions = new SortedSet<long>();
      for (int i = 0; i < n; i++) {
        // Initialize mappings for a[i] and b[i] to their indices
        if (!ids.ContainsKey(a[i]))
          ids.Add(a[i], new HashSet<int>());
        if (!ids.ContainsKey(b[i]))
          ids.Add(b[i], new HashSet<int>());
        ids[a[i]].Add(i);
        ids[b[i]].Add(i);
        ct[a[i] - 1]++;
        ct[b[i] - 1]++;
        // If a[i] == b[i], we must avoid this value being chosen in some rounds, 
        // so adjust o accordingly
        if (a[i] == b[i]) {
          if (!exclusions.Contains(a[i])) {
            exclusions.Add(a[i]);
            o *= n;
            o %= 998244353;
          } else {
            o = 0;
          }
        }
      }
      // If any value in 1..n is unused, Koxia cannot win
      if (ct.Contains(0) || o == 0) {
        o = 0;
      } else {
        Queue<int> q = new Queue<int>();
        // Find elements that appear in only one pair; these are 'leaf' nodes in the graph
        ids.Keys.ToList().ForEach(k => {
          if (ids[k].Count == 1 && !exclusions.Contains(k)) {
            q.Enqueue(ids[k].First());
          }
        });
        // Process nodes in a BFS fashion to find conflicting pairs
        while (q.Count > 0) {
          var id = q.Dequeue();
          var v1 = a[id];
          var v2 = b[id];
          // If either value no longer exists, Koxia cannot win
          if ((!ids.ContainsKey(v1)) || (!ids.ContainsKey(v2))) {
            o = 0;
            q = new Queue<int>();
            ids = new Dictionary<long, HashSet<int>>();
            break;
          }
          // Remove current index from mappings of v1 and v2
          ids[v1].Remove(id);
          ids[v2].Remove(id);
          // If one of v1 or v2 is left with no indices, Koxia cannot win
          if (ids[v1].Count == 0 && ids[v2].Count == 0) {
            o = 0;
            q = new Queue<int>();
            ids = new Dictionary<long, HashSet<int>>();
            break;
          }
          // Add new 'leaf' nodes to queue
          if (ids[v1].Count == 1 && !exclusions.Contains(v1))
            q.Enqueue(ids[v1].First());
          if (ids[v1].Count == 0)
            ids.Remove(v1);
          if (ids[v2].Count == 1 && !exclusions.Contains(v2))
            q.Enqueue(ids[v2].First());
          if (ids[v2].Count == 0)
            ids.Remove(v2);
        }
      }
      // Remove excluded elements from mapping
      exclusions.ToList().ForEach(e => { ids.Remove(e); });
      HashSet<long> unvisited = new HashSet<long>();
      // Find elements with exactly 2 indices, i.e., parts of the graph that may form cycles
      ids.Keys.ToList().ForEach(k => {
        if (ids[k].Count == 2)
          unvisited.Add(k);
      });
      // Process the cycles in the graph to count valid choices for c
      while (unvisited.Count > 0) {
        var w = unvisited.First();
        unvisited.Remove(w);
        long w2 = -1;
        // Find the next node in chain by examining neighbors
        var u2 = ids[w]
                     .Where(u => unvisited.Contains(a[u]) ||
                                 unvisited.Contains(b[u]))
                     .ToList();
        if (u2.Count == 0)
          break;
        int j = u2.First();
        if (a[j] != w)
          w2 = a[j];
        else if (b[j] != w)
          w2 = b[j];
        // Traverse the chain
        while (unvisited.Contains(w2)) {
          w = w2;
          unvisited.Remove(w);
          w2 = -1;
          if (ids[w].Count == 0)
            break;
          u2 = ids[w]
                   .Where(u => unvisited.Contains(a[u]) ||
                               unvisited.Contains(b[u]))
                   .ToList();
          if (u2.Count == 0)
            break;
          j = u2.First();
          if (a[j] != w)
            w2 = a[j];
          else if (b[j] != w)
            w2 = b[j];
        }
        // For cycle, we are allowed 2 choices per segment
        o *= 2;
        o %= 998244353;
      }
      o %= 998244353;
      output.Add(o.ToString());
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/