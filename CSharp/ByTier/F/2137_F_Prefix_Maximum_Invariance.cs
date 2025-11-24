// Problem: CF 2137 F - Prefix Maximum Invariance
// https://codeforces.com/contest/2137/problem/F

/*
F. Prefix Maximum Invariance

Algorithms/Techniques:
- Fenwick Tree (Binary Indexed Tree) for efficient range maximum queries and updates
- Offline processing with coordinate compression (reverse mapping)
- Sliding window technique combined with prefix logic to compute contributions

Time Complexity: O(n log n) per test case due to Fenwick tree operations and sorting
Space Complexity: O(n) for storing the input arrays and the Fenwick tree

Problem Summary:
Given two arrays a and b of size n, we want to compute the sum of f(al, ..., ar, bl, ..., br)
over all subarrays [l,r]. Here f(x,y) is the maximum number of positions where z_i = y_i
such that prefix maxima of z match those of x.

The approach processes each element from left to right using a Fenwick tree indexed by reversed values.
It maintains information about how many elements have been seen so far, enabling efficient queries on 
prefix maximums and counting overlapping elements under constraint of maintaining prefix maxima invariants.
*/

using System;
using System.Collections.Generic;
using System.Linq;
class FenwickMax {
  private int size;
  private int[] tree;
  public void Init(int n) {
    size = n;
    tree = new int[n + 1];
  }
  public void Update(int index, int value) {
    // Update the Fenwick Tree at index with value using bit manipulation
    for (; index <= size; index += index & -index) {
      tree[index] = Math.Max(tree[index], value);
    }
  }
  public int Query(int index) {
    // Query maximum value up to index using bit manipulation
    int result = 0;
    for (; index > 0; index -= index & -index) {
      result = Math.Max(result, tree[index]);
    }
    return result;
  }
}
class Program {
  static void Main() {
    string? line = Console.ReadLine();
    if (line == null)
      return;
    int t = int.Parse(line);
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()!);
      int[] a =
          Console.ReadLine()!.Split().Select(int.Parse).Prepend(0).ToArray(); // prepend 0 for 1-based indexing
      int[] b =
          Console.ReadLine()!.Split().Select(int.Parse).Prepend(0).ToArray(); // prepend 0 for 1-based indexing
      int maxVal = 2 * n;
      int Reverse(int v) => maxVal - v + 1; // coordinate compression to avoid negative indices
      var bit = new FenwickMax();
      bit.Init(maxVal + 2);
      long sum1 = 0, sum2 = 0;
      for (int i = 1; i <= n; i++) {
        // Find how many previous elements are >= a[i]: used to know where to place current element in z
        int prevGEa = bit.Query(Reverse(a[i]));
        // Update the Fenwick tree with current index of a[i]
        bit.Update(Reverse(a[i]), i);
        // Find how many previous elements are >= b[i]:
        int LGEb = bit.Query(Reverse(b[i]));
        long weight = n - i + 1; // number of subarrays starting at this position and ending in [i, n]
        sum1 += weight * LGEb; // contribution to sum1 from valid placements
        if (b[i] < a[i]) {
          // If b[i] < a[i], then the element b[i] can be chosen only after some previous element >= a[i]
          sum2 += weight * (i - prevGEa); // penalty term for overlapping elements
        }
      }
      Console.WriteLine(sum1 - sum2);
    }
  }
}


// https://github.com/VaHiX/codeForces/