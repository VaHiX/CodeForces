// Problem: CF 1709 D - Rorororobot
// https://codeforces.com/contest/1709/problem/D

/*
Purpose: Solve the Rorororobot problem where a robot moves through a grid with blocked cells,
         executing each command k times. Determine if a path exists from start to finish.

Algorithms/Techniques:
- Preprocessing with Sparse Table for range maximum queries on blocked cells
- Efficient collision detection using binary lifting technique

Time Complexity: O((n + m) * log(m) + q * log(m))
Space Complexity: O(m * log(m))

Where n is number of rows, m is number of columns, and q is number of queries.
*/
using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = 1;
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var b =
          Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList();
      var n = int.Parse(Console.ReadLine());
      List<int> p2 = new List<int>() { 1 };
      for (int i = 0; i < 18; i++)
        p2.Add(p2.Last() * 2);
      long[,] bm = new long[b.Count, 19];
      for (int i = 0; i < b.Count; i++) {
        bm[i, 0] = b[i];
      }
      for (int k = 1; k < 19; k++) {
        for (int i = 0; i < b.Count; i++) {
          bm[i, k] = Math.Max(bm[i, k - 1],
                              bm[Math.Min(i + p2[k - 1], b.Count - 1), k - 1]);
        }
      }
      for (int i = 0; i < n; i++) {
        bool can = false;
        var c =
            Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
        int k = c[4];
        // Check if the distance in both directions is divisible by k
        if ((c[2] - c[0]) % c[4] != 0 || (c[3] - c[1]) % c[4] != 0) {
          can = false;
        } else {
          // If moving in same column, path is always possible
          if (c[3] == c[1])
            can = true;
          else {
            // Calculate max height that needs to be avoided
            int height = Math.Max(c[0], c[2]);
            height = ((int)a[0] - height) % k;
            height = (int)a[0] - height;
            // Find the appropriate power of 2 for binary search
            var p =
                p2.IndexOf(p2.Where(t => t < Math.Abs(c[3] - c[1]) + 1).Max());
            var ll = Math.Min(c[3], c[1]) - 1;
            // Check if there's a collision using range max query
            if (bm[ll, p] >= height ||
                bm[ll + Math.Abs(c[3] - c[1]) + 1 - p2[p], p] >= height)
              can = false;
            else
              can = true;
          }
        }
        if (can)
          output.Add("YES");
        else
          output.Add("NO");
      }
    }
    output.ForEach(d => Console.WriteLine(d));
  }
}
}


// https://github.com/VaHiX/CodeForces/