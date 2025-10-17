// Problem: CF 2118 B - Make It Permutation
// https://codeforces.com/contest/2118/problem/B

/*
B. Make It Permutation
 Algorithms/Techniques: Greedy approach with row-wise subarray reversal.
 Time Complexity: O(n^2) per test case due to generating operations for each row.
 Space Complexity: O(1) excluding output storage.

 The matrix A is initially such that A[i][j] = j for all 1 <= i, j <= n.
 Our goal is to make every column a permutation of 1..n using at most 2*n operations.
 Each operation reverses a subarray in a specific row.

 Strategy:
 - Process rows in order from 1 to n.
 - For row i, we ensure that element i appears in column i (by appropriate reversal).
 - This is done by moving the required value into position via reversal operations.
 - The algorithm uses at most two operations per row.
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
    int t = input.readint();
    int mod = 1000000007;
    while (t-- > 0) {
      int n = input.readint();
      int k = 2 * n - 1; // Total number of operations needed (at most)
      print.WriteLine(k);
      for (int i = 1; i <= n; i++) {
        // Reverse entire row i to get the first element at position 1
        print.WriteLine($"{i} 1 {n - i + 1}");
        if (i > 1) {
          // Reverse subarray from column (n-i+2) to n in row i
          // This ensures that proper elements are moved for column permutation
          print.WriteLine($"{i} {n - i + 2} {n}");
          print.Flush();
        }
      }
    }
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