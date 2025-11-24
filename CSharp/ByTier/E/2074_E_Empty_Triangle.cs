// Problem: CF 2074 E - Empty Triangle
// https://codeforces.com/contest/2074/problem/E

/*
E. Empty Triangle
Algorithms/Techniques: Interactive problem using ternary search-like approach to find a triangle that contains no other points.
Time Complexity: O(n^2) in worst case due to up to 75 queries, but with careful selection of points, effectively finds solution quickly.
Space Complexity: O(1) - constant extra space used, not counting input/output.

This is an interactive problem where we need to find a triangle formed by three points such that no other hidden point lies inside it.
We use a strategy of querying triangles and using responses to narrow down the search space for valid triangles.
*/
using System;
public class Program {
  private const int MAX_QUERIES = 75;
  private static int queryCount = 0;
  private static int Query(int x, int y, int z) {
    if (queryCount >= MAX_QUERIES) {
      Environment.Exit(0);
    }
    Console.WriteLine($"? {x} {y} {z}");
    Console.Out.Flush();
    string input = Console.ReadLine();
    if (input == null) {
      Environment.Exit(0);
    }
    int response = int.Parse(input.Trim());
    if (response == -1) {
      Environment.Exit(0);
    }
    queryCount++;
    return response;
  }
  private static void SolveTestCase() {
    int n = int.Parse(Console.ReadLine().Trim());
    int a = 1, b = 2, c = 3; // Start with initial triangle points
    while (true) {
      int result = Query(a, b, c);
      if (result == 0) {
        break; // Found a valid triangle with no points inside
      }
      // Try to improve current triangle by replacing one point with the result of query
      if (Query(result, b, c) == 0) {
        a = result; // Replace 'a' with 'result', since it leads to valid triangle
        continue;
      }
      if (Query(a, result, c) == 0) {
        b = result; // Replace 'b' with 'result'
        continue;
      }
      if (Query(a, b, result) == 0) {
        c = result; // Replace 'c' with 'result'
        continue;
      }
      // If no single replacement works, do full update
      int newB = Query(result, b, c);
      int newC = Query(a, result, c);
      a = result;
      b = newB;
      c = newC;
    }
    Console.WriteLine($"! {a} {b} {c}");
    Console.Out.Flush();
  }
  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine().Trim());
    while (t-- > 0) {
      queryCount = 0;
      SolveTestCase();
    }
  }
}


// https://github.com/VaHiX/codeForces/