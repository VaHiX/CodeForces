// Problem: CF 2129 B - Stay or Mirror
// https://codeforces.com/contest/2129/problem/B

/* 
B. Stay or Mirror
Time Complexity: O(n log n) per test case due to sorting and segment tree operations
Space Complexity: O(n) for the segment tree and auxiliary arrays

Algorithms/Techniques:
- Sorting with index tracking
- Segment Tree for range queries and updates
- Greedy choice of whether to keep or mirror each element

The problem asks us to minimize inversions in a permutation after choosing,
for each element, to either keep it as is or mirror it (2*n - p[i]).
We use a segment tree to efficiently compute how many elements are smaller/larger
than the current one to the left/right, making greedy decisions.
*/

﻿using System.Text;
namespace StayOrMirror;
class Program {
  static long Solve() {
    int n = Next(); // Read number of elements
    var v = new int[n]; // Store original values
    var p = new int[n]; // Store their indices
    for (int i = 0; i < n; i++) {
      v[i] = Next(); // Read the permutation
      p[i] = i; // Store index
    }
    Array.Sort(v, p); // Sort by value while maintaining original indices
    var array = new int[n]; // Segment tree initialization - all 1s initially
    Array.Fill(array, 1);
    SegmentTree<int> tr = new(array, 0, (x, y) => x + y); // Create segment tree with sum operation
    long ans = 0; // Total inversions
    for (int i = 0; i < n; i++) {
      tr.Modify(p[i], 0); // Mark the element as used (set to 0)
      int l = tr.Query(0, p[i]); // Count of elements to the left that are still active
      int r = tr.Query(p[i], n); // Count of elements to the right that are still active
      ans += Math.Min(l, r); // Choose min to reduce inversions
    }
    return ans;
  }
  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve()); // Process each test case
    writer.Flush(); // Flush output
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
      Array.Copy(array, 0, t, n, n); // Copy initial values to leaf nodes
      Build(); // Build the segment tree
    }
    private void Build() {
      for (int i = n - 1; i > 0; --i) // Start from leaves and go up
        t[i] = operation(t[i << 1], t[i << 1 | 1]); // Combine children
    }
    public void Modify(int p, T value) {
      for (t[p += n] = value; p > 1; p >>= 1) // Update path from leaf to root
        t[p >> 1] = operation(t[p], t[p ^ 1]); // Merge sibling nodes with parent
    }
    public T Query(int l, int r) {
      T res = def;
      for (l += n, r += n; l < r; l >>= 1, r >>= 1) { // Traverse the tree
        if ((l & 1) == 1) // If left is a right child
          res = operation(res, t[l++]); // Add it and move forward
        if ((r & 1) == 1) // If right is a right child
          res = operation(res, t[--r]); // Subtract it and move backward
      }
      return res;
    }
  }
  static int Next() {
    int c;
    int m = 1;
    int res = 0;
    do {
      c = reader.Read(); // Read a character
      if (c == '-') // Handle negative sign
        m = -1;
    } while (c < '0' || c > '9'); // Skip until digit
    res = c - '0'; // Convert first digit
    while (true) {
      c = reader.Read(); // Read next character
      if (c < '0' || c > '9') // If not a digit, return result
        return m * res;
      res *= 10; // Multiply by 10
      res += c - '0'; // Add new digit
    }
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/