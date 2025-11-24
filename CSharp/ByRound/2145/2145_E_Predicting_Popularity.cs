// Problem: CF 2145 E - Predicting Popularity
// https://codeforces.com/contest/2145/problem/E

// Problem: Predicting Popularity
// Algorithms/Techniques: Segment Tree with Lazy Propagation, Simulation of Greedy Process
// Time Complexity: O(m * log n) where m is number of updates and n is number of users
// Space Complexity: O(n) for segment tree and user data structures

using System;
using System.IO;
public class Program {
  static long ac, dr;
  static int n, m;
  static long[] a, d;
  static long[] lazy;
  static long[] minH, maxH;
  static void Push(int v) {
    // Propagate lazy updates to child nodes
    if (lazy[v] != 0) {
      minH[v * 2] += lazy[v];
      maxH[v * 2] += lazy[v];
      lazy[v * 2] += lazy[v];
      minH[v * 2 + 1] += lazy[v];
      maxH[v * 2 + 1] += lazy[v];
      lazy[v * 2 + 1] += lazy[v];
      lazy[v] = 0;
    }
  }
  static void Pull(int v) {
    // Update parent node values based on children
    minH[v] = Math.Min(minH[v * 2], minH[v * 2 + 1]);
    maxH[v] = Math.Max(maxH[v * 2], maxH[v * 2 + 1]);
  }
  static void Build(int v, int tl, int tr) {
    // Build segment tree
    if (tl == tr) {
      minH[v] = maxH[v] = tl;
    } else {
      int tm = (tl + tr) / 2;
      Build(v * 2, tl, tm);
      Build(v * 2 + 1, tm + 1, tr);
      Pull(v);
    }
  }
  static void UpdateRange(int v, int tl, int tr, int l, int r, long add) {
    // Update a range in segment tree with lazy propagation
    if (l > r)
      return;
    if (l == tl && r == tr) {
      minH[v] += add;
      maxH[v] += add;
      lazy[v] += add;
    } else {
      Push(v);
      int tm = (tl + tr) / 2;
      UpdateRange(v * 2, tl, tm, l, Math.Min(r, tm), add);
      UpdateRange(v * 2 + 1, tm + 1, tr, Math.Max(l, tm + 1), r, add);
      Pull(v);
    }
  }
  static long QueryPoint(int v, int tl, int tr, int pos) {
    // Query specific position in segment tree
    if (tl == tr)
      return minH[v];
    Push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      return QueryPoint(v * 2, tl, tm, pos);
    else
      return QueryPoint(v * 2 + 1, tm + 1, tr, pos);
  }
  static int FindZero(int v, int tl, int tr, int pStart) {
    // Find first position where value becomes 0 or negative
    if (tr < pStart || maxH[v] < 0 || minH[v] > 0)
      return -1;
    if (tl == tr)
      return tl;
    Push(v);
    int tm = (tl + tr) / 2;
    int res = FindZero(v * 2, tl, tm, pStart);
    if (res != -1)
      return res;
    return FindZero(v * 2 + 1, tm + 1, tr, pStart);
  }
  static long CalculateCost(long curA, long curD) {
    // Calculate how much user needs to watch the movie (cost)
    return Math.Max(0L, curA - ac) + Math.Max(0L, curD - dr);
  }
  public static void Main() {
    var input =
        Console.In.ReadToEnd().Split(new char[] { ' ', '\n', '\r', '\t' },
                                     StringSplitOptions.RemoveEmptyEntries);
    int idx = 0;
    ac = long.Parse(input[idx++]);
    dr = long.Parse(input[idx++]);
    n = int.Parse(input[idx++]);
    a = new long[n + 1];
    d = new long[n + 1];
    for (int i = 1; i <= n; i++)
      a[i] = long.Parse(input[idx++]);
    for (int i = 1; i <= n; i++)
      d[i] = long.Parse(input[idx++]);
    int size = 4 * (n + 1);
    lazy = new long[size + 1];
    minH = new long[size + 1];
    maxH = new long[size + 1];
    Build(1, 0, n);
    for (int i = 1; i <= n; i++) {
      long cost = CalculateCost(a[i], d[i]);
      if (cost <= n)
        UpdateRange(1, 0, n, (int)cost, n, -1);
    }
    m = int.Parse(input[idx++]);
    while (m-- > 0) {
      int k = int.Parse(input[idx++]);
      long na = long.Parse(input[idx++]);
      long nd = long.Parse(input[idx++]);
      long oldCost = CalculateCost(a[k], d[k]);
      if (oldCost <= n)
        UpdateRange(1, 0, n, (int)oldCost, n, 1);
      a[k] = na;
      d[k] = nd;
      long newCost = CalculateCost(a[k], d[k]);
      if (newCost <= n)
        UpdateRange(1, 0, n, (int)newCost, n, -1);
      long h0 = QueryPoint(1, 0, n, 0);
      int pStart = (int)(-h0);
      int ans = FindZero(1, 0, n, pStart);
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/