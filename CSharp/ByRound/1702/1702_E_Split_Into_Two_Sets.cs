// Problem: CF 1702 E - Split Into Two Sets
// https://codeforces.com/contest/1702/problem/E

/*
Algorithm: Graph Coloring and Degree Check
Purpose: Determine if dominoes can be split into two sets such that all numbers in each set are distinct.

Approach:
1. Model the problem as a graph where each domino connects two nodes (numbers).
2. Check if any node has degree > 2, which makes splitting impossible (since each number can appear in at most 2 dominoes).
3. If degrees are acceptable, perform bipartite coloring on the graph to see if we can split into two sets.
4. If the graph is bipartite (can be colored with two colors), then splitting is possible.

Time Complexity: O(n + m) where n is number of dominoes and m is number of edges (sum of degree of all nodes).
Space Complexity: O(n + m) for storing adjacency lists and color information.
*/

using System;
using System.Linq;
using System.Numerics;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using N = System.Int64;
static class Program {
  static public void Main(string[] args) {
    Console.SetOut(
        new StreamWriter(Console.OpenStandardOutput()) { AutoFlush = false });
    var solver = new Solver();
    solver.Solve();
    Console.Out.Flush();
  }
}
public class Solver {
  public void Solve() {
    int t = ri;
    while (t-- > 0) {
      int n = ri;
      List<List<int>> g = new List<List<int>>(); // adjacency list
      for (int i = 0; i < n; i++) {
        g.Add(new List<int>());
      }
      for (int i = 0; i < n; i++) {
        int a = ri;
        int b = ri;
        // Convert to 0-based indexing and build adjacency list
        g[a - 1].Add(b - 1);
        g[b - 1].Add(a - 1);
      }
      bool good = true;
      // Check if any node has degree > 2
      for (int i = 0; i < n; i++) {
        if (g[i].Count() > 2)
          good = false;
      }
      if (!good) {
        Write("NO");
        continue;
      }
      // Initialize color array (0 = unvisited, 1 = color 1, 2 = color 2)
      List<int> color = new List<int>(n);
      for (int i = 0; i < n; i++) {
        color.Add(0);
      }
      // Perform BFS-based coloring
      for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
          color[i] = 1; // Start coloring with color 1
          Stack<int> st = new Stack<int>();
          st.Push(i);
          while (st.Count() > 0) {
            int j = st.Pop();
            int nc = 3 - color[j]; // Toggle color (1->2, 2->1)
            foreach (int v in g[j]) {
              if (color[v] == 0) {
                color[v] = nc;
                st.Push(v);
              } else {
                // If neighbor already colored and same as current node, not bipartite
                good = good && (color[v] == nc);
              }
            }
          }
        }
      }
      YN(good);
    }
  }
  const long inf = (long)1 << 60;
  int ri {
    get { return (int)sc.Integer(); }
  }
  long rl {
    get { return sc.Integer(); }
  }
  double rd {
    get { return sc.Double(); }
  }
  string rs {
    get { return sc.Scan(); }
  }
  public StreamScanner sc = new StreamScanner(Console.OpenStandardInput());
  void WriteJoin<T>(string s, T[] t) { Console.WriteLine(string.Join(s, t)); }
  void WriteJoin<T>(string s, List<T> t) {
    Console.WriteLine(string.Join(s, t));
  }
  void Write<T>(T t) { Console.WriteLine(t.ToString()); }
  void YN(bool t) { Console.WriteLine(t ? "YES" : "NO"); }
  void Yn(bool t) { Console.WriteLine(t ? "Yes" : "No"); }
  void yn(bool t) { Console.WriteLine(t ? "yes" : "no"); }
  void Swap(ref int x, ref int y) {
    x ^= y;
    y ^= x;
    x ^= y;
  }
  void Swap(ref N x, ref N y) {
    x ^= y;
    y ^= x;
    x ^= y;
  }
  void Swap<T>(ref T x, ref T y) {
    T t = y;
    y = x;
    x = t;
  }
}
public class StreamScanner {
  public StreamScanner(Stream stream) { str = stream; }
  private readonly Stream str;
  private readonly byte[] buf = new byte[1024];
  private int len, ptr;
  public bool isEof = false;
  public bool IsEndOfStream {
    get { return isEof; }
  }
  private byte read() {
    if (isEof)
      throw new EndOfStreamException();
    if (ptr >= len) {
      ptr = 0;
      if ((len = str.Read(buf, 0, 1024)) <= 0) {
        isEof = true;
        return 0;
      }
    }
    return buf[ptr++];
  }
  public char Char() {
    byte b = 0;
    do
      b = read();
    while (b < 33 || 126 < b);
    return (char)b;
  }
  public string Scan() {
    var sb = new StringBuilder();
    for (var b = Char(); b >= 33 && b <= 126; b = (char)read())
      sb.Append(b);
    return sb.ToString();
  }
  public long Integer() {
    long ret = 0;
    byte b = 0;
    var ng = false;
    do
      b = read();
    while (b != '-' && (b < '0' || '9' < b));
    if (b == '-') {
      ng = true;
      b = read();
    }
    for (; true; b = read()) {
      if (b < '0' || '9' < b)
        return ng ? -ret : ret;
      else
        ret = ret * 10 + b - '0';
    }
  }
  public double Double() { return double.Parse(Scan()); }
}


// https://github.com/VaHiX/CodeForces/