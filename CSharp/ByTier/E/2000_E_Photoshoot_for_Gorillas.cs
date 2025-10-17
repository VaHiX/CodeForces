// Problem: CF 2000 E - Photoshoot for Gorillas
// https://codeforces.com/contest/2000/problem/E

/*
 * Problem: E. Photoshoot for Gorillas
 * 
 * Purpose:
 *   This program finds the maximum "spectacle" of a gorilla photoshoot arranged in an n x m grid,
 *   where the spectacle is defined as the sum of all k x k square sub-squares' total gorilla heights.
 *   Gorillas are placed such that each cell has at most one gorilla, and we want to maximize the total spectacle.
 * 
 * Algorithm:
 *   1. Construct a "value map" for the grid that assigns weights to each cell based on how many k x k sub-squares it belongs to.
 *      - The center area of the grid gets higher weights (as they are part of more squares).
 *      - Bordering areas get values proportional to distance from edges and their contribution in k x k squares.
 *   2. Sort the gorilla heights in descending order (greedily assign largest to highest-weighted cells).
 *   3. Sort the map values in descending order.
 *   4. Multiply corresponding elements of the sorted arrays and sum them to get the maximum spectacle.
 * 
 * Time Complexity: O(n * m + w * log(w)) where w is the number of gorillas.
 * Space Complexity: O(n * m + w)
 */

using System.Collections.Generic;
using static System.Math;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var h = int.Parse(line[0]);
      var w = int.Parse(line[1]);
      var k = int.Parse(line[2]);
      var g = int.Parse(Console.ReadLine().Trim());
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, long.Parse);
      getAns(h, w, k, g, a);
    }
  }
  
  static void getAns(int h, int w, int k, int g, long[] a) {
    var map = new long[h, w];
    // Calculate the effective width and height of influence from edges
    var ww = Min(k, w - k + 1);
    var hh = Min(k, h - k + 1);
    
    // Initialize row and column influences for corner cells (based on proximity to edges)
    for (int i = 0; i < w; i++)
      map[0, i] = ww; // Row influence value, set to max possible edge coverage

    for (int i = 0; i < h; i++)
      map[i, 0] = hh; // Column influence value, set to max possible edge coverage

    // Fill values near top border (influence of rows)
    for (int i = 0; i < ww; i++) {
      map[0, i] = i + 1;
      map[0, w - 1 - i] = i + 1;
    }

    // Fill values near left border (influence of columns)
    for (int i = 0; i < hh; i++) {
      map[i, 0] = i + 1;
      map[h - 1 - i, 0] = i + 1;
    }
    
    // Propagate calculated values across other cells using multiplication
    for (int i = 1; i < h; i++)
      for (int j = 1; j < w; j++)
        map[i, j] = map[i, 0] * map[0, j]; // Multiply row and column influences to get cell weight
    
    // Gather all values from the map for sorting
    var aa = new List<long>();
    foreach (var x in map)
      aa.Add(x);
    
    // Sort map values in descending order for maximum benefit allocation
    aa.Sort();
    aa.Reverse();

    // Sort gorilla heights in descending order to match top-weighted cells
    Array.Sort(a);
    Array.Reverse(a);
    
    // Compute final result by pairing highest gorilla with highest weight cell
    var ans = 0L;
    for (int i = 0; i < g; i++)
      ans += a[i] * aa[i];
    
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/