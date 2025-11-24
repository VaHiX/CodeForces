// Problem: CF 1621 D - The Winter Hike
// https://codeforces.com/contest/1621/problem/D

/*
 * Problem: D. The Winter Hike
 * 
 * Algorithm/Techniques:
 * - Greedy approach to minimize cost of removing snow
 * - For each row/column, we identify the minimal cost to remove snow from critical positions
 * - The optimal strategy involves removing snow from the cheapest positions that prevent friends from reaching destination
 * 
 * Time Complexity: O(n^2) per test case
 * Space Complexity: O(n) per test case
 * 
 * Key idea:
 * - Friends start in top-left n×n grid and must end in bottom-right n×n grid
 * - Snow removal is only needed at specific positions to allow movement without getting stuck
 * - The critical positions are:
 *   - Top row (row 1): position n+1 (1-indexed), position 2n (1-indexed)
 *   - Bottom row (row n): position n+1 (1-indexed), position 2n (1-indexed)
 *   - Left column (col 1): position n+1 (1-indexed), position 2n (1-indexed)
 *   - Right column (col n): position n+1 (1-indexed), position 2n (1-indexed)
 * - For all rows from n+1 to 2n, we sum up the cost of removing snow in the right half (n to 2n)
 * - Then we pick the minimum cost among all critical positions (n+1, 2n) combinations for the 4 corners
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
      var n = int.Parse(Console.ReadLine());
      long o = 0; // Total cost of snow removal
      List<long> min = new List<long>(); // Stores costs of key positions
      for (int i = 0; i < 2 * n; i++) {
        var b =
            Console.ReadLine().Split(' ').Select(q => long.Parse(q)).ToList();
        if (i == 0) {
          // For top row, we consider positions n+1 and 2n (1-indexed)
          min.Add(b[n]); // Position (1, n+1)
          min.Add(b[2 * n - 1]); // Position (1, 2n)
        }
        if (i == n - 1) {
          // For row n, we consider positions n+1 and 2n (1-indexed)
          min.Add(b[n]); // Position (n, n+1)
          min.Add(b[2 * n - 1]); // Position (n, 2n)
        }
        if (i == n) {
          // For row n+1, we consider positions 1 and n (1-indexed)
          min.Add(b[0]); // Position (n+1, 1)
          min.Add(b[n - 1]); // Position (n+1, n)
        }
        if (i == 2 * n - 1) {
          // For bottom row, we consider positions 1 and n (1-indexed)
          min.Add(b[0]); // Position (2n, 1)
          min.Add(b[n - 1]); // Position (2n, n)
        }
        if (i >= n)
          // For rows from n+1 to 2n, we add cost of right half of the row (from position n+1 to 2n)
          o += b.GetRange(n, n).Sum();
      }
      // Add the minimum cost among the critical positions to total
      o += min.Min();
      output.Add(o.ToString());
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/