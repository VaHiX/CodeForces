// Problem: CF 1894 C - Anonymous Informant
// https://codeforces.com/contest/1894/problem/C

﻿/*
Purpose: Determine if a given array b can be obtained from some initial array a through k operations,
where each operation chooses a fixed point x and cyclically shifts the array left by x positions.
Algorithm: Simulation with cycle detection
Time Complexity: O(n + k) where n is the array length
Space Complexity: O(n) for the visited array
*/
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Numerics;
class Program {
  private static int Pos(int pos, int offset, int n) {
    pos += offset;
    if (pos < 1)
      pos += n;
    if (pos > n)
      pos -= n;
    return pos;
  }
  private static int[] SolveBf(int[] a, int k, int n) { return a; }
  private static bool Solve(int[] a, int k, int n) {
    // Track visited positions to detect cycles
    var visited = new bool[n];
    // Start from the last position (0-based index)
    var pos = n - 1;
    // Perform up to k operations
    for (int i = 0; i < k; i++) {
      // If we've visited this position before, we've entered a cycle
      if (visited[pos]) {
        return true;
      }
      visited[pos] = true;
      // If the value at current position exceeds array bounds, impossible
      if (a[pos] > n)
        return false;
      // Move according to the fixed point value
      pos -= a[pos];
      // Handle wraparound for negative indices
      if (pos < 0)
        pos += n;
    }
    return true;
  }
  private static void Main(string[] args) {
    PushTestData(@"
6
5 3
4 3 3 2 3
3 100
7 2 1
5 5
6 1 1 1 1
1 1000000000
1
8 48
9 10 11 12 13 14 15 8
2 1
1 42
Yes
Yes
No
Yes
Yes
No
");
    var t = RI();
    while (t-- > 0) {
      var n = RI();
      var k = RI();
      var m = RIA(n);
      Console.WriteLine(Solve(m, k, n) ? "Yes" : "No");
    }
  }
  private const int Mod = 1000000000 + 7;
#region Data Read
  private static int GCD(int a, int b) {
    if (a % b == 0)
      return b;
    return GCD(b, a % b);
  }
  private static List<int>[] ReadTree(int n) { return ReadGraph(n, n - 1); }
  private static List<int>[] ReadGraph(int n, int m) {
    List<int>[] g = new List<int>[n];
    for (int i = 0; i < g.Length; i++)
      g[i] = new List<int>();
    for (int i = 0; i < m; i++) {
      int a = RI() - 1;
      int b = RI() - 1;
      g[a].Add(b);
      g[b].Add(a);
    }
    return g;
  }
  private static int[,] ReadGraphAsMatrix(int n, int m) {
    int[,] matrix = new int[n + 1, n + 1];
    for (int i = 0; i < m; i++) {
      int a = RI();
      int b = RI();
      matrix[a, b] = matrix[b, a] = 1;
    }
    return matrix;
  }
  private static void Sort(ref int a, ref int b) {
    if (a > b)
      Swap(ref a, ref b);
  }
  private static void Swap(ref int a, ref int b) {
    int tmp = a;
    a = b;
    b = tmp;
  }
  private const int BufferSize = 1 << 16;
  private static StreamReader consoleReader;
  private static MemoryStream testData;
  private static int RI() {
    int ans = 0;
    int mul = 1;
    do {
      ans = consoleReader.Read();
      if (ans == -1)
        return 0;
      if (ans == '-')
        mul = -1;
    } while (ans < '0' || ans > '9');
    ans -= '0';
    while (true) {
      int chr = consoleReader.Read();
      if (chr < '0' || chr > '9')
        return ans * mul;
      ans = ans * 10 + chr - '0';
    }
  }
  private static long RL() {
    long ans = 0;
    int mul = 1;
    do {
      ans = consoleReader.Read();
      if (ans == -1)
        return 0;
      if (ans == '-')
        mul = -1;
    } while (ans < '0' || ans > '9');
    ans -= '0';
    while (true) {
      int chr = consoleReader.Read();
      if (chr < '0' || chr > '9')
        return ans * mul;
      ans = ans * 10 + chr - '0';
    }
  }
  private static int[] RIA(int n) {
    int[] ans = new int[n];
    for (int i = 0; i < n; i++)
      ans[i] = RI();
    return ans;
  }
  private static long[] RLA(int n) {
    long[] ans = new long[n];
    for (int i = 0; i < n; i++)
      ans[i] = RL();
    return ans;
  }
  private static char[] ReadWord() {
    int ans;
    do {
      ans = consoleReader.Read();
    } while (!((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z') ||
               (ans == '*')));
    List<char> s = new List<char>();
    do {
      s.Add((char)ans);
      ans = consoleReader.Read();
    } while ((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z') ||
             (ans == '*'));
    return s.ToArray();
  }
  private static char[] ReadString(int n) {
    int ans;
    do {
      ans = consoleReader.Read();
    } while (!((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z')));
    char[] s = new char[n];
    int pos = 0;
    do {
      s[pos++] = (char)ans;
      if (pos == n)
        break;
      ans = consoleReader.Read();
    } while ((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z'));
    return s;
  }
  private static char[] ReadStringLine() {
    int ans;
    do {
      ans = consoleReader.Read();
    } while (ans == 10 || ans == 13);
    List<char> s = new List<char>();
    do {
      s.Add((char)ans);
      ans = consoleReader.Read();
    } while (ans != 10 && ans != 13 && ans != -1);
    return s.ToArray();
  }
  private static char ReadLetter() {
    while (true) {
      int ans = consoleReader.Read();
      if ((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z'))
        return (char)ans;
    }
  }
  private static char ReadNonLetter() {
    while (true) {
      int ans = consoleReader.Read();
      if (!((ans >= 'a' && ans <= 'z') || (ans >= 'A' && ans <= 'Z')))
        return (char)ans;
    }
  }
  private static char ReadAnyOf(IEnumerable<char> allowed) {
    while (true) {
      char ans = (char)consoleReader.Read();
      if (allowed.Contains(ans))
        return ans;
    }
  }
  private static char ReadDigit() {
    while (true) {
      int ans = consoleReader.Read();
      if (ans >= '0' && ans <= '9')
        return (char)ans;
    }
  }
  private static int ReadDigitInt() { return ReadDigit() - (int)'0'; }
  private static char ReadAnyChar() { return (char)consoleReader.Read(); }
  private static string DoubleToString(double x) {
    return x.ToString(CultureInfo.InvariantCulture);
  }
  private static double DoubleFromString(string x) {
    return double.Parse(x, CultureInfo.InvariantCulture);
  }
  static Program() {
    consoleReader = new StreamReader(Console.OpenStandardInput(BufferSize),
                                     Encoding.ASCII, false, BufferSize);
  }
  private static void PushTestData(StringBuilder sb) {
    PushTestData(sb.ToString());
  }
  private static void PushTestData(string data) {
#if TOLYAN_TEST
    if (testData == null) {
      testData = new MemoryStream();
      consoleReader = new StreamReader(testData);
    }
    var pos = testData.Length;
    var bytes = Encoding.UTF8.GetBytes(data);
    testData.Write(bytes, 0, bytes.Length);
    testData.Flush();
    testData.Position = pos;
#endif
  }
#endregion
}


// https://github.com/VaHiX/CodeForces/