// Problem: CF 1869 B - 2D Traveling
// https://codeforces.com/contest/1869/problem/B

using System;

/// <summary>
/// Problem: 2D Traveling
/// Purpose: Find the minimum cost to travel from city 'a' to city 'b' on a 2D grid,
/// where some cities are major (free travel between them), others are not.
///
/// Algorithm:
/// - If there are no major cities (k == 0), the cost is simply the Manhattan distance between a and b.
/// - If there are major cities:
///   * Compute the minimum Manhattan distance from city 'a' to any major city.
///   * Compute the minimum Manhattan distance from city 'b' to any major city.
///   * Consider two paths:
///     1. Go from 'a' to a major city, then to 'b' (cost = min(a->major) + min(major->b))
///     2. Direct path from 'a' to 'b' (cost = Manhattan distance between a and b)
///   * Return the minimum of these two options.
///
/// Time Complexity: O(n + k) per test case, where n is number of cities and k is number of major cities.
/// Space Complexity: O(n) for storing city coordinates.
/// </summary>
public class _2DTraveling {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      int a = int.Parse(parts[2]);
      int b = int.Parse(parts[3]);
      int[] x = new int[n];
      int[] y = new int[n];
      for (int j = 0; j < n; j++) {
        parts = Console.ReadLine().Split();
        x[j] = int.Parse(parts[0]);
        y[j] = int.Parse(parts[1]);
      }
      long ans = 0;
      // Calculate Manhattan distance between a and b directly
      long dAB =
          (long)Math.Abs(x[a - 1] - x[b - 1]) + Math.Abs(y[a - 1] - y[b - 1]);
      if (k == 0)
        ans = dAB;
      else {
        // Initialize minimum distances from a and b to any major city
        long dAMin =
            (long)Math.Abs(x[0] - x[a - 1]) + Math.Abs(y[0] - y[a - 1]);
        long dBMin =
            (long)Math.Abs(x[0] - x[b - 1]) + Math.Abs(y[0] - y[b - 1]);
        for (int j = 1; j < k; j++) {
          // Update minimum distance from a to a major city
          dAMin = Math.Min(dAMin, (long)Math.Abs(x[j] - x[a - 1]) +
                                      Math.Abs(y[j] - y[a - 1]));
          // Update minimum distance from b to a major city
          dBMin = Math.Min(dBMin, (long)Math.Abs(x[j] - x[b - 1]) +
                                      Math.Abs(y[j] - y[b - 1]));
        }
        // Choose the minimum of direct path or path via major cities
        ans = Math.Min((long)dAMin + dBMin, dAB);
      }
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/