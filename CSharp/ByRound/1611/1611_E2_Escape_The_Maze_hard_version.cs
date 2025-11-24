// Problem: CF 1611 E2 - Escape The Maze (hard version)
// https://codeforces.com/contest/1611/problem/E2

// Purpose: Solve the "Escape The Maze (hard version)" problem where we need to find the minimum number of friends required to catch Vlad before he can escape.
// Algorithm: 
// 1. Build a tree from the given corridors
// 2. Find the distance from root (room 1) to all other nodes using BFS
// 3. Sort friends by their distance from root
// 4. Use a greedy approach to mark nodes that need to be covered
// 5. Run BFS again to determine if Vlad can escape and count minimum friends needed
// Time Complexity: O(n log n + n) where n is number of rooms, dominated by sorting
// Space Complexity: O(n) for storing tree structure, distances, and other arrays

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
namespace Escape_The_Maze__easy_version_ {
internal class Program {
  private static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  private static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
  private static void Main(string[] args) {
    int t = Next();
    for (int i = 0; i < t; i++) {
      Solve();
    }
    writer.Flush();
  }
  private static void Solve() {
    int n = Next();
    int k = Next();
    var kk = new int[k];
    for (int i = 0; i < k; i++) {
      kk[i] = Next() - 1;
    }
    var list = new List<int>[n];
    for (int i = 0; i < list.Length; i++) {
      list[i] = new List<int>();
    }
    for (int i = 1; i < n; i++) {
      int a = Next() - 1;
      int b = Next() - 1;
      list[a].Add(b);
      list[b].Add(a);
    }
    var p = new int[n];
    var d = new int[n];
    var f = new bool[n];
    var q = new Queue<int>();
    for (int i = 0; i < p.Length; i++) {
      p[i] = -1;
    }
    q.Enqueue(0);
    p[0] = 0;
    while (q.Count > 0) {
      int i = q.Dequeue();
      foreach (int j in list[i]) {
        if (p[j] == -1) {
          p[j] = i;
          d[j] = 1 + d[i];
          q.Enqueue(j);
        }
      }
    }
    p[0] = -1;
    Array.Sort(kk, new Sort(d));
    foreach (int e in kk) {
      int i = e;
      while (2 * d[i] >= d[e]) {
        if (f[i]) {
          break;
        }
        f[i] = true;
        i = p[i];
      }
    }
    for (int i = 0; i < p.Length; i++) {
      p[i] = -1;
    }
    p[0] = 1;
    bool fff = false;
    int count = 0;
    var qq = new Queue<Tuple<int, int>>();
    qq.Enqueue(new Tuple<int, int>(0, 0));
    while (qq.Count > 0) {
      Tuple<int, int> i = qq.Dequeue();
      if (i.Item1 != 0 && list[i.Item1].Count == 1 && i.Item2 == 0)
        fff = true;
      foreach (int j in list[i.Item1]) {
        if (p[j] == -1) {
          if (f[j]) {
            if (i.Item2 == 1) {
            } else {
              count++;
            }
            p[j] = 1;
            qq.Enqueue(new Tuple<int, int>(j, 1));
          } else {
            p[j] = 1;
            qq.Enqueue(new Tuple<int, int>(j, i.Item2));
          }
        }
      }
    }
    if (fff)
      writer.WriteLine("-1");
    else
      writer.WriteLine(count);
  }
  private static int Next() {
    int c;
    int res = 0;
    do {
      c = reader.Read();
      if (c == -1)
        return res;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return res;
      res *= 10;
      res += c - '0';
    }
  }
#region Nested type : Sort
  private class Sort : IComparer<int> {
    private readonly int[] _w;
    public Sort(int[] w) { _w = w; }
#region IComparer < int> Members
    public int Compare(int x, int y) { return _w[x].CompareTo(_w[y]); }
#endregion
  }
#endregion
}
}


// https://github.com/VaHiX/CodeForces/