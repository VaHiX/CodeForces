// Problem: CF 2116 C - Gellyfish and Flaming Peony
// https://codeforces.com/contest/2116/problem/C

/*
C. Gellyfish and Flaming Peony
Problem Description:
Given an array of positive integers, we need to make all elements equal by repeatedly replacing one element with the GCD of itself and another element. The goal is to find the minimum number of such operations.

Algorithms:
- Use BFS (Breadth-First Search) to compute shortest distances from each unique value to the overall GCD of the array.
- Preprocess unique values in the input array to avoid redundant computation.
- If there is already an element equal to the global GCD, we can reduce the count of operations.

Time Complexity: O(n * sqrt(max_val) + sqrt(max_val)^2)
Space Complexity: O(max_val)

*/
using System;
using System.Collections.Generic;
using System.Text;
class Program {
  static int Gcd(int a, int b) {
    while (b != 0) {
      int t = a % b;
      a = b;
      b = t;
    }
    return a;
  }
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    var output = new StringBuilder();
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var parts = Console.ReadLine().Split();
      int[] a = new int[n];
      int g = 0;
      int maxA = 0;
      for (int i = 0; i < n; i++) {
        a[i] = int.Parse(parts[i]);
        if (i == 0)
          g = a[i];
        else
          g = Gcd(g, a[i]); // Compute global GCD of all elements
        if (a[i] > maxA)
          maxA = a[i]; // Track maximum value for distance array
      }
      int countG = 0;
      var seen = new bool[maxA + 1];
      var unique = new List<int>();
      foreach (var v in a) {
        if (v == g)
          countG++; // Count how many elements are already equal to GCD
        if (!seen[v]) {
          seen[v] = true;
          unique.Add(v); // Store unique values in the array
        }
      }
      if (countG > 0) {
        output.Append(n - countG).Append('\n'); // If some value is already GCD, just need to change others (n-countG)
        continue;
      }
      int m = unique.Count;
      var dist = new int[maxA + 1]; // Distance array for BFS
      for (int i = 1; i <= maxA; i++)
        dist[i] = -1; // Initialize distances as -1 (unvisited)
      var queue = new int[maxA + 1]; // BFS queue
      int head = 0, tail = 0;
      foreach (var v in unique) {
        dist[v] = 0; // All initial unique values are at distance 0
        queue[tail++] = v; // Add to queue for BFS
      }
      while (head < tail) {
        int x = queue[head++]; // Pop from queue
        if (x == g)
          break; // Stop when we reach the global GCD
        int dx = dist[x];
        for (int i = 0; i < m; i++) {
          int y = unique[i];
          int z = Gcd(x, y); // Compute GCD of current value and another unique value
          if (dist[z] == -1) { // If not yet visited
            dist[z] = dx + 1; // Increment distance
            queue[tail++] = z; // Add to queue for future exploration
          }
        }
      }
      int cost = dist[g]; // Find minimum steps to reduce all elements to GCD
      output.Append(cost + (n - 1)).Append('\n'); // Final answer combines BFS result and n-1 operations
    }
    Console.Write(output.ToString());
  }
}


// https://github.com/VaHiX/CodeForces/