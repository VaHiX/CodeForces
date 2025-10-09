// Problem: CF 2121 D - 1709
// https://codeforces.com/contest/2121/problem/D

/*
 * Problem: D. 1709 - Sorting arrays with specific conditions using swaps.
 *
 * Purpose:
 * This code takes two arrays 'a' and 'b', each containing distinct integers from 1 to 2*n,
 * and performs a series of allowed operations to satisfy the following conditions:
 * 1. Both arrays are sorted in ascending order.
 * 2. For all i, a[i] < b[i].
 *
 * Algorithms/Techniques Used:
 * - Bubble sort-like approach for sorting arrays individually (passes through elements).
 * - Swapping between arrays when necessary to maintain a[i] < b[i].
 *
 * Time Complexity:
 * O(n^3) in worst case. This is due to nested loops for sorting (O(n^2)) and additional
 * passes for swapping values, with up to 1709 operations allowed.
 *
 * Space Complexity:
 * O(n) for storing the arrays and the list of operations.
 */

using System;
using System.Collections.Generic;

class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      int[] b = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      var ops = new List<(int type, int index)>();
      
      // Bubble sort for array 'a'
      for (int pass = 0; pass < n; ++pass) {
        for (int i = 0; i + 1 < n; ++i) {
          if (a[i] > a[i + 1]) {
            (a[i], a[i + 1]) = (a[i + 1], a[i]); // Swap adjacent elements
            ops.Add((1, i + 1)); // Add operation to swap a[i] and a[i+1]
          }
        }
      }
      
      // Bubble sort for array 'b'
      for (int pass = 0; pass < n; ++pass) {
        for (int i = 0; i + 1 < n; ++i) {
          if (b[i] > b[i + 1]) {
            (b[i], b[i + 1]) = (b[i + 1], b[i]); // Swap adjacent elements
            ops.Add((2, i + 1)); // Add operation to swap b[i] and b[i+1]
          }
        }
      }
      
      // Ensure a[i] < b[i] for all valid indices
      for (int i = 0; i < n; ++i) {
        if (a[i] > b[i]) {
          (a[i], b[i]) = (b[i], a[i]); // Swap elements between arrays
          ops.Add((3, i + 1)); // Add operation to swap a[i] and b[i]
        }
      }
      
      Console.WriteLine(ops.Count);
      foreach (var (type, index) in ops) {
        Console.WriteLine($"{type} {index}");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/