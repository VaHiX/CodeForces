// Problem: CF 2133 C - The Nether
// https://codeforces.com/contest/2133/problem/C

/*
C. The Nether

Purpose:
This program solves an interactive problem involving finding the longest path in a directed acyclic graph (DAG) of portals.
The algorithm uses queries to determine the longest path by first identifying the node with the maximum path length,
then backtracking through the graph to reconstruct the full path.

Algorithms/Techniques:
1. Binary search technique combined with DFS-like traversal
2. Graph traversal using query-based inference
3. Iterative path reconstruction via backtracking

Time Complexity: O(n^2)
Space Complexity: O(n)

The solution makes at most 2*n queries and has a time complexity proportional to the square of the number of nodes due to nested loops in path reconstruction.
*/

﻿using System.Text;
namespace TheNether;
class Program {
  static void Solve() {
    int n = int.Parse(reader.ReadLine());
    int[] kk = new int[n];
    for (int i = 1; i <= n; i++) {
      kk[i - 1] = i;
    }
    int[] ans = new int[n];
    for (int i = 1; i <= n; i++) {
      ans[i - 1] = Ask(i, kk); // Query each node to get the longest path starting from it
    }
    int max = 0;
    for (int i = 0; i < ans.Length; i++) {
      if (ans[i] > ans[max])
        max = i; // Find node with maximum path length
    }
    List<int> aa = new() { max }; // Start path reconstruction from the node with max path
    while (ans[aa[^1]] != 1) { // Continue until we reach a node with path length 1
      for (int i = 0; i < ans.Length; i++) {
        if (ans[i] + 1 == ans[aa[^1]]) { // If previous node has one less in path length
          int p = Ask(aa[^1] + 1, i + 1); // Query to check connection between nodes
          if (p == 2) {
            aa.Add(i); // Add connected node to the path
            break;
          }
        }
      }
    }
    Ans(aa.ToArray()); // Output the final path
  }
  static int Ask(int x, int y) {
    writer.WriteLine($"? {x} 2 {x} {y}");
    writer.Flush();
    return int.Parse(reader.ReadLine());
  }
  static int Ask(int x, int[] kk) {
    writer.Write($"? {x} {kk.Length}");
    foreach (var k in kk) {
      writer.Write(' ');
      writer.Write(k);
    }
    writer.WriteLine();
    writer.Flush();
    return int.Parse(reader.ReadLine());
  }
  static void Ans(int[] kk) {
    writer.Write($"! {kk.Length}");
    foreach (var k in kk) {
      writer.Write(' ');
      writer.Write(k + 1); // Convert to 1-based indexing
    }
    writer.WriteLine();
    writer.Flush();
  }
  static void Main(string[] args) {
    int t = int.Parse(reader.ReadLine());
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/