// Problem: CF 2130 C - Double Perspective
// https://codeforces.com/contest/2130/problem/C

/*
C. Double Perspective
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
For a set of pairs S = {(a1, b1), (a2, b2), ..., (am, bm)}, where ai < bi for all 1 <= i <= m, we define f(S) and g(S) as follows:

f(S): The length of the union of segments on the number line.
g(S): The number of nodes that lie on at least one simple cycle with at least 3 edges in the graph formed by treating each (ai, bi) as an undirected edge.

Algorithm:
- Use Union-Find to detect cycles and greedily select segments such that we try to
  minimize the number of nodes involved in cycles while maximizing union length.
- Sort segments by their length and use Union-Find to build connected components,
  selecting a segment only if it connects two different components (i.e., avoids creating a cycle).
- The idea is to prefer longer segments when possible so that the total length (f) is maximized, but avoid adding edges that would form small cycles.
- f(S) is calculated by merging overlapping intervals on the number line.
- g(S) is effectively approximated by counting how many nodes are part of cycles; this implementation uses Union-Find to track connectivity and avoids forming cycles, thereby minimizing g(S).

Time Complexity: O(n^2 * α(n)) where α(n) is the inverse Ackermann function (nearly constant), due to sorting and Union-Find operations.
Space Complexity: O(n) for storing segments and union-find arrays.

*/

using System;
using System.Collections.Generic;
using System.Linq;
class DoublePerspectiveSolver {
  class Segment {
    public int A, B, Index;
    public Segment(int a, int b, int index) {
      A = a;
      B = b;
      Index = index;
    }
  }
  static int[] parent;
  static void InitUnionFind(int size) {
    parent = new int[size + 1];
    for (int i = 0; i <= size; i++)
      parent[i] = i;
  }
  static int Find(int x) {
    if (parent[x] != x)
      parent[x] = Find(parent[x]); // Path compression
    return parent[x];
  }
  static bool Union(int x, int y) {
    int px = Find(x);
    int py = Find(y);
    if (px == py)
      return false; // Already in same set, forming a cycle
    parent[px] = py; // Union the sets
    return true;
  }
  static int GetUnionLength(List<Segment> segments) {
    if (segments.Count == 0)
      return 0;
    segments.Sort((s1, s2) => s1.A != s2.A ? s1.A.CompareTo(s2.A)
                                           : s1.B.CompareTo(s2.B));
    int total = 0;
    int curStart = segments[0].A;
    int curEnd = segments[0].B;
    foreach (var s in segments) {
      if (s.A <= curEnd) {
        curEnd = Math.Max(curEnd, s.B); // Merge overlapping segments
      } else {
        total += curEnd - curStart; // Add the length of previous merged segment
        curStart = s.A;
        curEnd = s.B;
      }
    }
    total += curEnd - curStart;
    return total;
  }
  static void Solve() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var segments = new List<Segment>();
      for (int i = 0; i < n; i++) {
        var parts = Console.ReadLine().Split().Select(int.Parse).ToArray();
        segments.Add(new Segment(parts[0], parts[1], i + 1));
      }
      segments.Sort((s1, s2) => (s1.B - s1.A).CompareTo(s2.B - s2.A)); // Sort by length
      InitUnionFind(2 * n + 1);
      List<Segment> selected = new List<Segment>();
      foreach (var seg in segments) {
        if (Union(seg.A, seg.B)) // Only add edge if no cycle is created
          selected.Add(seg);
      }
      Console.WriteLine(selected.Count);
      Console.WriteLine(string.Join(" ", selected.Select(s => s.Index)));
    }
  }
  static void Main() {
    Solve();
        
  }
}


// https://github.com/VaHiX/CodeForces/