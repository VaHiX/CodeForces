// Problem: CF 1905 B - Begginer's Zelda
// https://codeforces.com/contest/1905/problem/B

using System;
public class BeginnerSZelda {
  // Purpose: Determine the minimum number of Zelda operations to reduce a tree to a single vertex.
  // Algorithm: The key insight is that each operation merges a path, effectively reducing the number of leaf nodes.
  //            The minimum number of operations equals the ceiling of (number of leaves - 2) / 2.
  // Time Complexity: O(n) for each test case where n is the number of vertices.
  // Space Complexity: O(n) for storing the degree array.
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      int[] degs = new int[n]; // Array to store degree of each vertex
      int numEdge = n - 1;
      for (int j = 0; j < numEdge; j++) {
        string[] parts = Console.ReadLine().Split();
        degs[int.Parse(parts[0]) - 1]++; // Increment degree of first vertex
        degs[int.Parse(parts[1]) - 1]++; // Increment degree of second vertex
      }
      int ans = 0;
      for (int j = 0; j < n; j++)
        ans += Math.Max(0, degs[j] - 2); // Count internal nodes (degree >= 3) contributing to operations
      ans = (ans + 3) / 2; // Apply ceiling division by 2 to get minimum operations
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/