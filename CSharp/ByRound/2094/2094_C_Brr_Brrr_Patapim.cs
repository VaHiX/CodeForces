// Problem: CF 2094 C - Brr Brrr Patapim
// https://codeforces.com/contest/2094/problem/C

/*
 * Problem: C. Brr Brrr Patapim
 * Purpose: Given an n×n grid where G[i,j] = p[i+j], reconstruct the permutation p of length 2*n.
 * Algorithm: 
 *   - For each diagonal (i + j = k), we know that all elements on this diagonal are part of the permutation.
 *   - We iterate through diagonals and collect known values from the grid into array b.
 *   - Unknown positions (where G[i,j] = 0) in b[] are filled with remaining unused numbers from [1, 2*n].
 * Time Complexity: O(n^2) per test case due to scanning the grid and processing diagonals.
 * Space Complexity: O(n^2) for storing the grid, plus O(n) for auxiliary arrays (b and c), overall O(n^2).
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      getAns(n);
    }
  }
  static void getAns(int n) {
    var a = new int[n, n];
    for (int i = 0; i < n; i++) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      for (int j = 0; j < n; j++)
        a[i, j] = int.Parse(line[j]);
    }
    var b = new int[2 * n]; // Stores the reconstructed permutation indexed by (i + j)
    var hs = Enumerable.Range(1, 2 * n).ToHashSet(); // Set of available numbers [1..2*n]
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        b[i + j + 1] = a[i, j]; // Fill the result array with known values based on diagonal index
        hs.Remove(a[i, j]); // Remove used numbers from set
      }
    }
    var c = hs.ToArray(); // Remaining unused numbers to fill in zeros
    for (int i = 0; i < 2 * n; i++) {
      if (b[i] == 0)
        b[i] = c[0]; // Assign one of the remaining numbers
    }
    Console.WriteLine(string.Join(" ", b));
  }
}


// https://github.com/VaHiX/codeForces/