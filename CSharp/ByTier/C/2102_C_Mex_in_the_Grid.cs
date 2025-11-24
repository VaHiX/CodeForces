// Problem: CF 2102 C - Mex in the Grid
// https://codeforces.com/contest/2102/problem/C

/*
C. Mex in the Grid
Algorithm: Spiral traversal of grid to place numbers in a way that maximizes sum of MEX over all subgrids.
Time Complexity: O(n^2) per test case due to filling the grid and outputting.
Space Complexity: O(n^2) for storing the grid.

The solution uses a spiral pattern starting from center (or near-center), placing values in a way that avoids forming small MEX values in many subgrids,
which helps maximize total sum. The key idea is to use a specific traversal order and numbering scheme to spread out low values and delay appearance of 
small missing numbers in subgrids.
*/

using System.Text;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      getAns(n);
    }
  }
  static void print(int n, int[,] map) {
    var sb = new StringBuilder();
    var p = new int[n];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        p[j] = map[i, j];
      sb.AppendLine(string.Join(" ", p));
    }
    Console.Write(sb);
  }
  static void getAns(int n) {
    var map = new int[n, n];
    var dx = new int[] { 0, 1, 0, -1 }; // Direction vectors for right, down, left, up
    var dy = new int[] { 1, 0, -1, 0 };
    var k = 2 * n - 1;
    var a = new int[k];
    var w = 0;
    for (int i = 0; i < k - 1; i++) {
      if (i % 2 == 0)
        w++;
      a[i] = w;
    }
    a[k - 1] = n - 1;
    var x = n % 2 == 0 ? (n - 1) / 2 : n / 2; // Starting position near center
    var y = x;
    var p = 0;
    map[x, y] = p++; // Start placing from the center or near-center
    for (int i = 0; i < n * 2 - 1; i++) {
      for (int j = 0; j < a[i]; j++) {
        x += dx[i % 4];
        y += dy[i % 4];
        map[x, y] = p++;
      }
    }
    print(n, map);
  }
}


// https://github.com/VaHiX/codeForces/