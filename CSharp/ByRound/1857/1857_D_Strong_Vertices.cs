// Problem: CF 1857 D - Strong Vertices
// https://codeforces.com/contest/1857/problem/D

/*
 * Problem: Find all "strong vertices" in a directed graph constructed from two arrays a and b.
 * 
 * Algorithm:
 * - For each vertex u, compute score = a[u] - b[u].
 * - A vertex is strong if it has the maximum score among all vertices.
 * - This is because if a[u] - a[v] >= b[u] - b[v], then a[u] - b[u] >= a[v] - b[v].
 *   So, a vertex u can reach all other vertices if and only if its score is the maximum.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the scores and result list
 */
using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
      int[] b = Console.ReadLine().Split().Select(int.Parse).ToArray();
      List<int> strongVertices = FindStrongVertices(n, a, b);
      Console.WriteLine(strongVertices.Count);
      Console.WriteLine(string.Join(" ", strongVertices));
    }
  }
  static List<int> FindStrongVertices(int n, int[] a, int[] b) {
    List<int> strongVertices = new List<int>();
    int[] score = new int[n];
    for (int i = 0; i < n; i++) {
      score[i] = a[i] - b[i];  // Compute the score for each vertex
    }
    int maxScore = score.Max();  // Find the maximum score
    for (int i = 0; i < n; i++) {
      if (score[i] == maxScore) {  // If score equals max, vertex is strong
        strongVertices.Add(i + 1);  // Add vertex number (1-indexed)
      }
    }
    return strongVertices;
  }
}


// https://github.com/VaHiX/CodeForces/