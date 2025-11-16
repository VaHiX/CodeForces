// Problem: CF 1774 E - Two Chess Pieces
// https://codeforces.com/contest/1774/problem/E

/*
 * Problem: Two Chess Pieces on a Tree
 * 
 * Purpose: 
 *   Given a tree with n nodes and two pieces initially at node 1, each piece must visit a set of nodes.
 *   The pieces can move to adjacent nodes, but their distance must never exceed d.
 *   Find the minimum number of moves required for both pieces to visit all necessary nodes and return to root.
 * 
 * Approach:
 *   1. Build the tree from input edges.
 *   2. Identify all required nodes for each piece using sets.
 *   3. For each piece, simulate DFS traversal to identify additional nodes that need to be visited based on distance constraint.
 *   4. Calculate minimum moves for each piece to visit their required nodes and return to root.
 * 
 * Time Complexity: O(n)
 *   - Building the tree: O(n)
 *   - DFS traversal: O(n)
 *   - Visiting required nodes: O(n)
 *   - Total: O(n)
 * 
 * Space Complexity: O(n)
 *   - Tree storage: O(n)
 *   - DFS recursion stack: O(n) in worst case
 *   - Other data structures: O(n)
 * 
 * Algorithms/Techniques:
 *   - Tree traversal (DFS)
 *   - Distance constraint handling
 *   - Set operations for node tracking
 *   - Path tracking and backtracking
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static int[] parent;
  public static List<int>[] edges;
  public static HashSet<int> m1 = new HashSet<int>();
  public static HashSet<int> m2 = new HashSet<int>();
  static List<int> extram1 = new List<int>();
  static List<int> extram2 = new List<int>();
  static int d = 1;
  public static List<int> path = new List<int>();
  public static void GoDeep(int id) {
    path.Add(id);
    if (m1.Contains(id) && path.Count > d) // If current node is required by piece 1 and path is longer than d
      extram2.Add(path[path.Count - 1 - d]); // Add node d steps back in path to piece 2's extra nodes
    if (m2.Contains(id) && path.Count > d) // If current node is required by piece 2 and path is longer than d
      extram1.Add(path[path.Count - 1 - d]); // Add node d steps back in path to piece 1's extra nodes
    edges[id].ForEach(r => {
      if (parent[id] != r) { // If not parent
        parent[r] = id;
        GoDeep(r); // Continue DFS
      }
    });
    path.RemoveAt(path.Count - 1); // Backtrack
  }
  public static void Main(string[] args) {
    int count = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      long o = 0;
      long n = a[0];
      d = (int)a[1]; // Read distance constraint
      edges = new List<int>[n];
      for (int i = 0; i < n; i++) {
        edges[i] = new List<int>(); // Initialize adjacency list
      }
      for (int i = 0; i < n - 1; i++) {
        var b =
            Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
        edges[b[0] - 1].Add(b[1] - 1); // Add bidirectional edges
        edges[b[1] - 1].Add(b[0] - 1);
      }
      parent = new int[n]; // Parent tracking for DFS
      parent[0] = -1; // Root has no parent
      var l1 = Console.ReadLine()
                   .Split(' ')
                   .Select(qw => int.Parse(qw) - 1)
                   .ToList(); // Read first piece's path
      var l2 = Console.ReadLine()
                   .Split(' ')
                   .Select(qw => int.Parse(qw) - 1)
                   .ToList(); // Read second piece's path
      l1.RemoveAt(0); // Remove count from list
      l2.RemoveAt(0);
      m1 = new HashSet<int>(l1); // Convert to hashset for fast lookups
      m2 = new HashSet<int>(l2);
      Stack<int> q = new Stack<int>();
      q.Push(0);
      while (q.Count > 0) {
        int id = q.Pop();
        if (path.Count > 0) {
          while (path.Last() != parent[id]) // While last node in path isn't parent of current node
            path.RemoveAt(path.Count - 1); // Backtrack path
        }
        path.Add(id); // Add current node to path
        if (m1.Contains(id) && path.Count > d) // If node is required by piece 1 and path is longer than d
          extram2.Add(path[path.Count - 1 - d]); // Add node d steps back to piece 2's set
        if (m2.Contains(id) && path.Count > d) // If node is required by piece 2 and path is longer than d
          extram1.Add(path[path.Count - 1 - d]); // Add node d steps back to piece 1's set
        edges[id].ForEach(r => {
          if (parent[id] != r) { // If not parent
            parent[r] = id;
            q.Push(r); // Push child to stack
          }
        });
      }
      extram1.ForEach(m => m1.Add(m)); // Add additional required nodes to set
      extram2.ForEach(m => m2.Add(m));
      int[] visited = new int[n];
      visited[0] = 1; // Mark root as visited
      l1 = m1.ToList(); // Convert required nodes to list
      for (int i = 0; i < l1.Count; i++) {
        int y = l1[i];
        while (y != 0) { // While we haven't reached root
          if (visited[y] == 0) { // If not visited
            o += 2; // Add 2 steps (go to node, come back)
            visited[y] = 1; // Mark as visited
            y = parent[y]; // Move to parent
          } else {
            break; // If already visited, break
          }
        }
      }
      visited = new int[n];
      visited[0] = 1; // Reset visited array
      l1 = m2.ToList(); // Convert second piece's required nodes
      for (int i = 0; i < l1.Count; i++) {
        int y = l1[i];
        while (y != 0) { // While not root
          if (visited[y] == 0) { // If not visited
            o += 2; // Add 2 steps
            visited[y] = 1; // Mark visited
            y = parent[y]; // Go to parent
          } else {
            break; // Already visited, break
          }
        }
      }
      output.Add(o.ToString()); // Add result to output
    }
    string on = string.Join("\n", output);
    Console.WriteLine(on);
  }
}
}


// https://github.com/VaHiX/CodeForces/