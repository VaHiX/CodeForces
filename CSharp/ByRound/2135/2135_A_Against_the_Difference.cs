// Problem: CF 2135 A - Against the Difference
// https://codeforces.com/contest/2135/problem/A

/*
 * Problem: Longest Neat Subsequence
 *
 * A block is an array where all elements are equal to the length of the array.
 * An array is called neat if it can be obtained by concatenating blocks.
 * Task: Find the length of the longest neat subsequence of given array a.
 *
 * Approach:
 * 1. For each element, store indices where it appears in the original array.
 * 2. Use a segment tree with dynamic programming:
 *    - At each position i, determine the maximum length of a neat subsequence ending at i.
 *    - Transition: for current value a[i], we look back to previous occurrences
 *      and try extending sequences using the block property.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

﻿using System.Text;
namespace AA;
class Program {
  static int Solve() {
    int n = Next(); // Read input size
    int[] a = new int[n]; // Store array elements
    var nn = new Dictionary<int, List<int>>(); // Map value to list of indices where it occurs
    for (int i = 0; i < n; i++) {
      a[i] = Next(); // Read next element
      if (nn.TryGetValue(a[i], out List<int> l)) {
        l.Add(i); // Add index to existing list
      } else {
        nn[a[i]] = new List<int>() { i }; // Create new list with this index
      }
    }
    SegmentTree<int> tr = new SegmentTree<int>(new int[n], 0, Math.Max); // Initialize segment tree for max queries
    for (int i = 0; i < n; i++) {
      List<int> ll = nn[a[i]]; // Get list of indices for current value
      int index = ll.BinarySearch(i); // Find where current index is in the list
      if (index - a[i] + 1 >= 0) { // Check bounds before accessing
        tr.Modify(i, a[i] + tr.Query(0, ll[index - a[i] + 1])); // Update tree with new value from query
      }
    }
    return tr.Query(0, n); // Return the maximum value in the range [0,n)
  }

  private class SegmentTree<T> {
    public delegate T Op(T x, T y);
    private readonly int n;
    private readonly T[] t;
    private readonly T def;
    private readonly Op operation;

    public SegmentTree(T[] array, T def, Op operation) {
      n = array.Length;
      this.def = def;
      this.operation = operation;
      t = new T[2 * n];
      Array.Copy(array, 0, t, n, n); // Copy input to leaves of segment tree
      Build(); // Build the tree
    }

    private void Build() {
      for (int i = n - 1; i > 0; --i)
        t[i] = operation(t[i << 1], t[i << 1 | 1]); // Compute parent nodes from children
    }

    public void Modify(int p, T value) {
      for (t[p += n] = value; p > 1; p >>= 1) // Start at leaf node and propagate up
        t[p >> 1] = operation(t[p], t[p ^ 1]); // Update parent with operation of sibling and itself
    }

    public T Query(int l, int r) {
      T res = def;
      for (l += n, r += n; l < r; l >>= 1, r >>= 1) { // Traverse ranges from bottom to top
        if ((l & 1) == 1)
          res = operation(res, t[l++]); // If l is odd, include it and increment
        if ((r & 1) == 1)
          res = operation(res, t[--r]); // If r is odd, decrement and include
      }
      return res;
    }
  }

  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve()); // Process each case
    writer.Flush();
  }

  static int Next() {
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9'); // Skip non-digits until digit found
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res; // Done reading number
      res *= 10;
      res += c - '0'; // Build the number digit by digit
    }
  }

  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/