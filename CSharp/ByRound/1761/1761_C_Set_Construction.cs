// Problem: CF 1761 C - Set Construction
// https://codeforces.com/contest/1761/problem/C

/* 
 * Problem: Set Construction
 * 
 * Purpose: Given a binary matrix b representing subset relationships, construct n sets A1, A2, ..., An such that Ai ⊂ A_j if and only if b[i][j] = 1.
 * 
 * Algorithm:
 * - Use a topological sorting approach with BFS to determine the subset relationships.
 * - Identify nodes with no incoming edges (st[i] == 0) as starting points.
 * - For each node, update the transitive closure of subset relationships.
 * - Each set A_i contains elements j where o[i][j] == 1.
 * 
 * Time Complexity: O(n^3) due to nested loops for transitive closure
 * Space Complexity: O(n^2) for the matrix o and auxiliary arrays
 */

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static Queue<int> q; // Queue for BFS traversal
  public static int[,] o; // Matrix to store subset relationships (transitive closure)
  public static string[] d; // Input matrix as strings
  public static int[] st; // Array to track nodes with incoming edges
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> output = new List<string>(); // Store output lines
    for (int z = 0; z < count; z++) {
      var n = int.Parse(Console.ReadLine()); // Read size of matrix
      d = new string[n];
      o = new int[n, n];
      q = new Queue<int>();
      st = new int[n];
      for (int i = 0; i < n; i++) {
        d[i] = Console.ReadLine(); // Read input matrix row by row
        for (int j = 0; j < n; j++) {
          o[i, j] = 0; // Initialize the relationship matrix
          if (d[i][j] == '1')
            st[j] = 1; // Mark nodes with incoming edges
        }
      }
      for (int i = 0; i < n; i++) {
        if (st[i] == 0) { // Add nodes with no incoming edges to queue
          q.Enqueue(i);
        }
      }
      while (q.Count > 0) {
        var start = q.Dequeue(); // Get node from queue
        o[start, start] = 1; // A set is a subset of itself
        for (int i = 0; i < n; i++) {
          if (d[start][i] == '1') { // If start is a proper subset of i
            for (int j = 0; j < n; j++) {
              o[i, j] = Math.Max(o[i, j], o[start, j]); // Update transitive closure
            }
            if (!q.Contains(i)) // Add to queue if not already there
              q.Enqueue(i);
          }
        }
      }
      for (int i = 0; i < n; i++) {
        List<string> t = new List<string>(); // Build set for A_i
        for (int j = 0; j < n; j++) {
          if (o[i, j] == 1) // If j is element of set A_i
            t.Add((j + 1).ToString()); // Add j+1 (1-indexed)
        }
        output.Add(t.Count + " " + string.Join(" ", t)); // Format output for set A_i
      }
    }
    string on = string.Join("\n", output); // Join all output lines
    Console.WriteLine(on); // Print final output
  }
}
}


// https://github.com/VaHiX/CodeForces/