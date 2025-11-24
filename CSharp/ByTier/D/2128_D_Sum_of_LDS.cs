// Problem: CF 2128 D - Sum of LDS
// https://codeforces.com/contest/2128/problem/D

/*
 * Problem: D. Sum of LDS
 * Purpose: Compute the sum of length of longest decreasing subsequence (LDS) 
 *          over all subarrays of a given permutation satisfying a specific constraint.
 *
 * Algorithm:
 * - Use dynamic programming with reverse iteration on the array to compute dp[i]
 *   which represents the contribution of subarrays starting at index i.
 * - The recurrence is based on comparing adjacent elements and building upon previous values.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using ll = System.Int64;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.Intrinsics.Arm;

class CP {
  static void Main() {
    var input = new FastReader();
    var print =
        new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    int t1 = input.readint();
    int mod = 1000000007;
    int mod1 = 998244353;
    while (t1-- > 0) {
      int n = input.readint();
      var arr = input.IntList(n);
      var dp = new List<ll>();
      for (int i = 0; i < n + 1; i++) {
        dp.Add(0);
      }
      dp[n - 1] = 1;
      // Fill dp array from right to left
      for (int i = n - 2; i >= 0; i--) {
        if (arr[i] > arr[i + 1]) {
          // If current element is greater than next, extend the sequence
          dp[i] = dp[i + 1] + n - i;
        } else {
          // Otherwise take jump two positions
          dp[i] = dp[i + 2] + n - i;
        }
      }
      ll ans = 0;
      // Sum all contributions
      for (int i = 0; i < n; i++) {
        ans += dp[i];
      }
      print.WriteLine(ans);
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
  public double readdouble() {
    double n = 0, div = 1;
    byte c = Skip();
    bool dec = false, neg = false;
    if (c == '-') {
      neg = true;
      c = Read();
    }
    while ((c >= '0' && c <= '9') || c == '.') {
      if (c == '.') {
        dec = true;
        c = Read();
        continue;
      }
      if (!dec)
        n = n * 10 + (c - '0');
      else {
        div *= 10;
        n += (c - '0') / div;
      }
      c = Read();
    }
    return neg ? -n : n;
  }
  public string readstring() {
    var sb = new StringBuilder();
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
  public long[] LongArray(int n) {
    var a = new long[n];
    for (int i = 0; i < n; i++)
      a[i] = readlong();
    return a;
  }
  public string[] StringArray(int n) {
    var a = new string[n];
    for (int i = 0; i < n; i++)
      a[i] = readstring();
    return a;
  }
  public List<int> IntList(int n) {
    var list = new List<int>(n);
    for (int i = 0; i < n; i++)
      list.Add(readint());
    return list;
  }
  public List<long> LongList(int n) {
    var list = new List<long>(n);
    for (int i = 0; i < n; i++)
      list.Add(readlong());
    return list;
  }
  public List<string> StringList(int n) {
    var list = new List<string>(n);
    for (int i = 0; i < n; i++)
      list.Add(readstring());
    return list;
  }
}


// https://github.com/VaHiX/codeForces/