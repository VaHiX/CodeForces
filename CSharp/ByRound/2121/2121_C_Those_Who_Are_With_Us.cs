// Problem: CF 2121 C - Those Who Are With Us
// https://codeforces.com/contest/2121/problem/C

/*
 * Problem: C. Those Who Are With Us
 * 
 * Purpose:
 *   Given an n x m matrix of integers, perform exactly one operation where we choose a row r and column c,
 *   then decrease all elements in that row and column by 1. The goal is to minimize the maximum value in the matrix.
 * 
 * Algorithm:
 *   - For each test case, find the maximum value 'mv' in the matrix.
 *   - Identify all positions where this maximum occurs.
 *   - If there are 2 or fewer such positions, we can reduce the max by 1 (just one operation).
 *   - Otherwise, check if we can reduce the max further by checking:
 *     - If all but one of the maximum positions lie on a common row, reducing that row may help.
 *     - Similarly for columns.
 *   - Use helper functions 'checkx' and 'checky' to validate these conditions.
 * 
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for storing the matrix and positions
 */

using static System.Math;
using System.Collections.Generic;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var h = int.Parse(line[0]);
      var w = int.Parse(line[1]);
      getAns(h, w);
    }
  }

  // Check if we can reduce the max by 1 by reducing a column
  static bool checky(List<(int x, int y)> a) {
    var d = new Dictionary<int, int>();
    foreach (var z in a)
      if (d.ContainsKey(z.y))
        d[z.y]++;
      else
        d[z.y] = 1;
    var over2 = new List<int>();
    foreach (var z in d)
      if (z.Value > 1)
        over2.Add(z.Key);
    if (over2.Count != 1)
      return false;
    var tt = over2[0];
    var b = new HashSet<int>();
    foreach (var z in a)
      if (z.y != tt)
        b.Add(z.x);
    return b.Count <= 1;
  }

  // Check if we can reduce the max by 1 by reducing a row
  static bool checkx(List<(int x, int y)> a) {
    var d = new Dictionary<int, int>();
    foreach (var z in a)
      if (d.ContainsKey(z.x))
        d[z.x]++;
      else
        d[z.x] = 1;
    var over2 = new List<int>();
    foreach (var z in d)
      if (z.Value > 1)
        over2.Add(z.Key);
    if (over2.Count != 1)
      return false;
    var tt = over2[0];
    var b = new HashSet<int>();
    foreach (var z in a)
      if (z.x != tt)
        b.Add(z.y);
    return b.Count <= 1;
  }

  // Main function to compute the result
  static void getAns(int h, int w) {
    var map = new int[h, w];
    var mv = -1;
    for (int i = 0; i < h; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      for (int j = 0; j < w; j++) {
        var t = int.Parse(line[j]);
        mv = Max(mv, t);
        map[i, j] = t;
      }
    }

    // If matrix is a single row or column, we can always reduce the max by one
    if (h == 1 | w == 1) {
      Console.WriteLine(mv - 1);
      return;
    }

    var aa = new List<(int x, int y)>();
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (map[i, j] == mv)
          aa.Add((i, j));
      }
    }

    // If there are at most two maximum elements, we can reduce the max by one
    if (aa.Count <= 2) {
      Console.WriteLine(mv - 1);
      return;
    }

    var cx = checkx(aa);
    var cy = checky(aa);
    Console.WriteLine(cx | cy ? mv - 1 : mv);
  }
}


// https://github.com/VaHiX/CodeForces/