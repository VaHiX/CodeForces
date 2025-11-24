// Problem: CF 2120 C - Divine Tree
// https://codeforces.com/contest/2120/problem/C

/*
 * C. Divine Tree
 *
 * Problem Description:
 * Given n nodes and desired total divineness m, construct a rooted tree such that 
 * the sum of d(v) (smallest node on path from root to v) is exactly m.
 *
 * Algorithm:
 * - For a tree with n nodes and m total divineness:
 *   - The minimum possible sum is n (each node points to itself or parent is the smallest),
 *     and maximum is n*(n+1)/2 (path from 1 to n forming a chain).
 *   - The difference between actual m and minimum (m - n) determines how many edges
 *     we need to rearrange to "push" the divineness values higher.
 *   - The approach uses a greedy construction:
 *     - First, create a chain from 1 to n with edges (i, i+1).
 *     - Then modify a few edges to adjust total divineness.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n)
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using ll = System.Int64;

class CP {
  static void Main() {
    var input = new FastReader();
    var print =
        new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    int t1 = input.readint();
    int mod = 1000000007;
    while (t1-- > 0) {
      int n = input.readint();
      ll m = input.readlong();
      ll m1 = n;
      ll m2 = (ll)n * (n + 1) / 2;
      if (m < m1 || m > m2) {
        print.WriteLine("-1");
        continue;
      }
      if (n == m) {
        print.WriteLine(1);
        for (int i = 1; i < n; i++)
          print.WriteLine($"{i} {i + 1}");
        continue;
      }
      ll op = m - n;
      int[] ans = new int[n + 2];
      for (int i = 0; i < ans.Length; i++)
        ans[i] = -1;
      int c1 = 1, l = n - 1;
      ll op1 = -1;
      while (op > 0) {
        ll can = n - c1;
        if (can >= op) {
          ans[c1] = (int)(l - (can - op));
          op1 = l - (can - op);
          c1++;
          break;
        } else {
          ans[c1++] = l--;
          op -= can;
        }
      }
      int n1 = 0;
      for (int i = c1; i <= n; i++) {
        if (op1 == n1) {
          n1++;
          i--;
          continue;
        }
        ans[i] = n1++;
      }
      int[] a = new int[n + 1];
      for (int i = 1; i <= n; i++)
        a[ans[i]] = i;
      print.WriteLine(a[0]);
      for (int i = 0; i < n - 1; i++)
        print.WriteLine($"{a[i]} {a[i + 1]}");
    }
    print.Flush();
  }
}

class FastReader {
  private readonly Stream s;
  private readonly byte[] b = new byte[1 << 18];
  private int l, p;
  public FastReader() { s = Console.OpenStandardInput(); }
  private byte Read() {
    if (p >= l) {
      p = 0;
      l = s.Read(b, 0, b.Length);
      if (l == 0)
        return 0;
    }
    return b[p++];
  }
  private byte Skip() {
    byte c;
    while ((c = Read()) <= 32)
      ;
    return c;
  }
  public int readint() {
    int n = 0, sgn = 1;
    byte c = Skip();
    if (c == '-') {
      sgn = -1;
      c = Read();
    }
    while (c >= '0' && c <= '9') {
      n = n * 10 + (c - '0');
      c = Read();
    }
    return n * sgn;
  }
  public long readlong() {
    long n = 0, sgn = 1;
    byte c = Skip();
    if (c == '-') {
      sgn = -1;
      c = Read();
    }
    while (c >= '0' && c <= '9') {
      n = n * 10 + (c - '0');
      c = Read();
    }
    return n * sgn;
  }
  public string readstring() {
    var sb = new System.Text.StringBuilder();
    byte c = Skip();
    while (c > 32) {
      sb.Append((char)c);
      c = Read();
    }
    return sb.ToString();
  }
  public int[] IntArray(int n) {
    var a = new int[n];
    for (int i = 0; i < n; i++)
      a[i] = readint();
    return a;
  }
  public List<int> IntList(int n) {
    var list = new List<int>(n);
    for (int i = 0; i < n; i++)
      list.Add(readint());
    return list;
  }
}


// https://github.com/VaHiX/codeForces/