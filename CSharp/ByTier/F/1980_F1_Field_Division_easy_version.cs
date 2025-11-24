// Problem: CF 1980 F1 - Field Division (easy version)
// https://codeforces.com/contest/1980/problem/F1

/*
 * Problem: F1. Field Division (easy version)
 * 
 * Purpose: Determine the maximum area Alice can claim when dividing a field with fountains,
 *          and for each fountain, decide if giving it to Alice increases her area.
 * 
 * Approach:
 *   - Model the field and fountains as a grid.
 *   - Alice starts from the top or left side and moves only right or down.
 *   - The optimal path for Alice is such that it ends at bottom or right side.
 *   - The path that maximizes Alice's area determines the division.
 *   - For each fountain, check if giving it to Alice allows a better path.
 * 
 * Time Complexity: O(k log k) per test case due to sorting operations.
 * Space Complexity: O(k) for storing fountains and intermediate results.
 */

using System;
using System.Collections.Generic;
using System.Linq;
public class Program {
  static void Solve() {
    long n, m, k;
    var input = Console.ReadLine().Split().Select(long.Parse).ToArray();
    n = input[0];
    m = input[1];
    k = input[2];
    List<long> cols = new List<long>(); // Collect column coordinates of fountains
    cols.Add(m + 1); // Add a sentinel column beyond the field
    List<Tuple<long, long>> pts = new List<Tuple<long, long>>(); // Store fountain coordinates
    Dictionary<long, List<Tuple<long, long>>> fts =
        new Dictionary<long, List<Tuple<long, long>>>();
    // Group fountains by column
    for (long i = 0; i < k; i++) {
      var point = Console.ReadLine().Split().Select(long.Parse).ToArray();
      pts.Add(new Tuple<long, long>(point[0], point[1]));
      cols.Add(point[1]); // Add to column list for sorting
      if (!fts.ContainsKey(point[1]))
        fts[point[1]] = new List<Tuple<long, long>>();
      fts[point[1]].Add(new Tuple<long, long>(point[0], i)); // Store row and index of fountain
    }
    fts[m + 1] = new List<Tuple<long, long>>();
    fts[m + 1].Add(new Tuple<long, long>(n, -1)); // Sentinel for final column
    List<long> isImp = Enumerable.Repeat((long)0, (int)k).ToList(); // Flag to track improved fountains
    long currCol = 1; // Current column being processed
    long currRow = 1; // Current row being processed
    cols = cols.Distinct().ToList(); // Remove duplicate columns
    cols.Sort(); // Sort columns to process from left to right
    long ans = 0; // Maximum area Alice can get without any fountain
    foreach (var c in cols) {
      fts[c].Sort((a, b) => b.Item1.CompareTo(a.Item1)); // Sort by row descending to get highest first
      foreach (var tuple in fts[c]) {
        var r = tuple.Item1; // Row of fountain
        var ind = tuple.Item2; // Index of fountain in original list
        if (r < currRow)
          continue; // Skip if fountain is below current path
        else {
          // Add area from previous column to current column
          ans += (c - currCol) * (n - currRow + 1);
          currRow = r + 1; // Move current row past this fountain
          currCol = c; // Update current column
          if (ind != -1)
            isImp[(int)ind] = 1; // Mark fountain as improving the area
        }
      }
    }
    Console.WriteLine(ans);
    Console.WriteLine(string.Join(" ", isImp));
  }
  public static void Main(string[] args) {
    long totalTests = long.Parse(Console.ReadLine());
    for (long testNo = 1; testNo <= totalTests; testNo++) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/CodeForces/