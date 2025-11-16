// Problem: CF 1722 F - L-shapes
// https://codeforces.com/contest/1722/problem/F

/*
 * Problem: F. L-shapes
 * 
 * Approach:
 * 1. The algorithm processes a grid to determine if it consists entirely of valid L-shapes.
 * 2. An L-shape is defined as three connected '*' cells forming an L-shape (can be rotated).
 * 3. Each L-shape must be isolated (no adjacent shapes touching by edge or corner).
 * 
 * Time Complexity: O(n * m) where n is the number of rows and m is the number of columns.
 * Space Complexity: O(n * m) for storing the grid and auxiliary data structures.
 * 
 * Algorithm Details:
 * - Pad the grid with '.' characters to avoid boundary checks.
 * - Identify all '*' cells and process them through BFS-like logic to form L-shapes.
 * - For each L-shape, ensure it contains exactly 3 cells and forms a valid L-shape (no more than 2 units in any direction).
 * - Maintain a queue to track unprocessed '*' cells.
 * - Validate connected components for being valid L-shapes.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
namespace Compete2 {
partial class MainClass {
  public static List<Tuple<int, int>> HasN(Tuple<int, int> r, List<string> d) {
    List<Tuple<int, int>> l = new List<Tuple<int, int>>();
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0)
          continue; // Skip the current cell itself
        if (d[r.Item1 + i][r.Item2 + j] == '*') {
          l.Add(new Tuple<int, int>(r.Item1 + i, r.Item2 + j));
        }
      }
    }
    return l;
  }
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine());
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      bool can = true;
      List<string> d = new List<string>();
      string s = "";
      for (int j = 0; j < a[1] + 2; j++) {
        s += '.';
      }
      d.Add(s);
      for (int i = 0; i < a[0]; i++) {
        s = "." + Console.ReadLine() + ".";
        d.Add(s);
      }
      s = "";
      for (int j = 0; j < a[1] + 2; j++) {
        s += '.';
      }
      d.Add(s);
      Queue<Tuple<int, int>> t = new Queue<Tuple<int, int>>();
      for (int i = 1; i < a[0] + 1; i++) {
        for (int j = 1; j < a[1] + 1; j++) {
          if (d[i][j] == '*') {
            t.Enqueue(new Tuple<int, int>(i, j)); // enqueue all '*' cells for processing
          }
        }
      }
      while (t.Count > 0) {
        var r = t.Dequeue();
        List<Tuple<int, int>> q = new List<Tuple<int, int>>();
        Queue<Tuple<int, int>> q1 = new Queue<Tuple<int, int>>();
        q.Add(r);
        var ne = HasN(q.Last(), d); // get neighbors of the last added cell
        while (ne.Count + q1.Count > 1) { // continue building the shape
          ne.Where(y => !q.Contains(y)).ToList().ForEach(y => q1.Enqueue(y)); // add new neighbors
          q.Add(q1.Dequeue());
          if (q.Count > 3) {
            can = false;
            break;
          }
          // Check if the shape exceeds L-shape dimensions (exceeds 2 units in either direction)
          if (q.Max(u => u.Item1) - q.Min(u => u.Item1) > 2 ||
              q.Max(u => u.Item2) - q.Min(u => u.Item2) > 2) {
            can = false;
            break;
          }
          ne = HasN(q.Last(), d).Where(y => !q.Contains(y)).ToList(); // update neighbors
        }
        if (q.Count != 3) // each valid L-shape must have exactly 3 cells
          can = false;
        if (!can)
          break;
      }
      if (can)
        output.Add("YES");
      else
        output.Add("NO");
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/