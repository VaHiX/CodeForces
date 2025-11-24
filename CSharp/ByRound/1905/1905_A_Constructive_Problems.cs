// Problem: CF 1905 A - Constructive Problems
// https://codeforces.com/contest/1905/problem/A

/*
 * Gridlandia Reconstruction Problem
 * 
 * Problem Description:
 * We are given an n x m grid representing Gridlandia, where each cell is a city.
 * Initially, all cities are collapsed. The government can choose to rebuild some cities.
 * A collapsed city can be rebuilt if it has at least one rebuilt city vertically adjacent
 * and at least one rebuilt city horizontally adjacent.
 * 
 * Goal: Find the minimum number of cities the government needs to initially rebuild
 * so that all cities can eventually be rebuilt through the aid mechanism.
 * 
 * Algorithm:
 * The key insight is to observe that we can use a "checkerboard" pattern to cover all
 * cells. Specifically, a minimal set of cities to start with is one that ensures that
 * every cell in the grid can be reached by the propagation rule.
 * 
 * The optimal approach is to place the initial rebuilt cities in a way that maximizes
 * coverage. A simple and effective method is to place cities in a diagonal pattern.
 * 
 * Observation:
 * For any grid, placing cities at positions (1,1), (1,3), (1,5), ..., and so on
 * in a pattern that covers the grid efficiently is sufficient.
 * 
 * However, a simpler and more optimal solution is:
 * - We can cover the grid by placing cells such that every cell is either:
 *   1. Already rebuilt, or
 *   2. Has at least one horizontally and one vertically adjacent rebuilt cell.
 * 
 * A minimal set is to select the larger of the two dimensions, as we can cover
 * the smaller dimension by placing 1 city per row/column.
 * 
 * Example:
 * n=2, m=2
 * We need at least 2 cities (e.g., (1,2) and (2,1))
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), ignoring the output buffer.
 */

using System;
using System.Text;
public class ConstructiveProblems {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte n = byte.Parse(parts[0]);
      byte m = byte.Parse(parts[1]);
      // The minimum number of cities needed is the maximum of n and m.
      // This is because placing cities in a way such that they span
      // the largest dimension ensures full coverage.
      byte ansi = Math.Max(n, m);
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/